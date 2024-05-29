# Exercise 47: A Fast URL Router

## Notes

- misc
  - book uses `urls.txt` instead of `ex47_urls.txt` as the file for manuall testing `urlor.c`
- todos
  - [x] get the copy-pasted source code to compile and build
  - [x] type-copy the source code into `./modded`
  - [x] add code comments to `./modded`
  - [x] read text and add notes here
  - [x] watch video and add notes here

## Extra Credit

- [ ] ~~1. Instead of just storing the string for the handler, create an actual engine that uses a `Handler` struct to store the application. The structure would store the URL to which it's attached, the name, and anything else you'd need to make an actual routing system.~~
  - Skipped
- [ ] ~~2. Instead of mapping URLs to arbitrary names, map them to .so files and use the `dlopen` system to load handlers on the fly and call callbacks they contain. Put these callbacks that in your `Handler `struct, and then you have yourself a fully dynamic callback handler system in C.~~
  - Skipped
