set -e

c_binary="devpkg"

clear
echo ">>>>>>>>>>> Running tests for '$c_binary'"
echo ""

# Command 1: Setup
echo "> Command 1: Setup"
echo "\$ $c_binary -S"
$c_binary -S
echo ""

# Command 2: Install
echo "> Command 2: Install"
echo "\$ $c_binary -I https://dlcdn.apache.org/httpd/httpd-2.4.59.tar.gz"
$c_binary -I https://dlcdn.apache.org/httpd/httpd-2.4.59.tar.gz
echo ""

# Command 3: List
echo "> Command 3: List"
echo "\$ $c_binary -L"
$c_binary -L
echo ""

# Command 4: Fetch
echo "> Command 4: Fetch"
echo "\$ $c_binary -F https://dlcdn.apache.org/httpd/httpd-2.4.59.tar.gz"
$c_binary -F https://dlcdn.apache.org/httpd/httpd-2.4.59.tar.gz
echo ""

# Command 5: Build
echo "> Command 5: Build"
echo "\$ $c_binary -B https://dlcdn.apache.org/httpd/httpd-2.4.59.tar.gz"
$c_binary -B https://dlcdn.apache.org/httpd/httpd-2.4.59.tar.gz
echo ""
