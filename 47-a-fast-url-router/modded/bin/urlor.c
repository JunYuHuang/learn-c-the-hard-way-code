/*
I'm now going to show you how I use the `TSTree` to do fast URL
routing in Web servers that I've written. This works for simple URL
routing you might use at the edge of an application, but doesn't
really work for the more complex (and sometimes unnecessary) routing
found in many Web application frameworks.

To play with routing, I'm going to make a little command line tool
that I'm calling `urlor`, which reads a simple file of routes, and
then prompts the user to enter in URLs.

...

You can see that the routing system first tries an exact match, and
if it can't find one, it will give a prefix match. This is mostly
done to try out the difference between the two. Depending on the
semantics of your URLs, you may want to always match exactly, always
to prefixes, or do both and pick the best one.
*/

#include <lcthw/tstree.h>
#include <lcthw/bstrlib.h>

TSTree *add_route_data(TSTree *routes, bstring line)
{
    struct bstrList *data = bsplit(line, ' ');
    check(data != NULL, "Bad data from bsplit.");
    check(
        data->qty == 2,
        "Line '%s' does not have 2 columns",
        bdata(line)
    );

    routes = TSTree_insert(
        routes,
        bdata(data->entry[0]),
        blength(data->entry[0]),
        bstrcpy(data->entry[1])
    );

    bstrListDestroy(data);

    return routes;

error:
    if (data) bstrListDestroy(data);
    return NULL;
}

TSTree *load_routes(const char *file)
{
    TSTree *routes = NULL;
    bstring line = NULL;
    FILE *routes_map = NULL;

    routes_map = fopen(file, "r");
    check(
        routes_map != NULL,
        "Failed to open routes: %s",
        file
    );

    while (
        (line = bgets((bNgetc) fgetc, routes_map, '\n')) != NULL
    ) {
        check(btrimws(line) == BSTR_OK, "Failed to trim line.");
        routes = add_route_data(routes, line);
        check(routes != NULL, "Failed to add route.");
        bdestroy(line);
        line = NULL;    // for error cleanup
    }

    fclose(routes_map);
    return routes;

error:
    if (routes_map) fclose(routes_map);
    if (line) bdestroy(line);

    return NULL;
}

bstring match_url(TSTree *routes, bstring url, int *out_prefix)
{
    bstring route = TSTree_search(routes, bdata(url), blength(url));

    if (route) {
        *out_prefix = 0;
    } else {
        *out_prefix = 1;
        printf("No exact match found, trying prefix.\n");
        route = TSTree_search_prefix(
            routes, bdata(url), blength(url)
        );
    }

    return route;
}

bstring read_line(const char *prompt)
{
    printf("%s", prompt);

    bstring result = bgets((bNgetc) fgetc, stdin, '\n');
    check_debug(result != NULL, "stdin closed.");

    check(btrimws(result) == BSTR_OK, "Failed to trim.");

    return result;

error:
    if (result) bdestroy(result);
    return NULL;
}

void bdestroy_cb(void *value, void *ignored)
{
    (void)ignored;
    bdestroy((bstring) value);
}

void destroy_routes(TSTree *routes)
{
    TSTree_traverse(routes, bdestroy_cb, NULL);
    TSTree_destroy(routes);
}

int main(int argc, char *argv[])
{
    bstring url = NULL;
    bstring route = NULL;
    TSTree *routes = NULL;
    int prefix = 0;

    check(argc == 2, "USAGE: urlor <urlfile>");

    routes = load_routes(argv[1]);
    check(routes != NULL, "Your route file has an error.");

    // BUG: only ctrl-c to get out of this?
    while (1) {
        url = read_line("URL> ");
        check_debug(url != NULL, "goodbye.");

        route = match_url(routes, url, &prefix);

        if (route) {
            if (prefix) {
                printf(
                    "PREFIX MATCH: %s == %s\n",
                    bdata(url),
                    bdata(route)
                );
            } else {
                printf(
                    "EXACT MATCH: %s == %s\n",
                    bdata(url),
                    bdata(route)
                );
            }
        } else {
            printf("FAIL: %s\n", bdata(url));
        }

        bdestroy(url);
    }

    destroy_routes(routes);
    return 0;

error:
    if (routes) destroy_routes(routes);
    return 1;
}
