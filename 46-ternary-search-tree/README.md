# Exercise 46: Ternary Search Tree

## Notes

- ternary search tree
  - like a BST but
    - with 3 branches per node
    - each char in the key's string maps to its own node
  - a special trie or prefix tree with 3 node pointers per node
  - pros
    - fast to find by prefix if you reverse the keys inserted
    - fast approximate matching (i.e. similar strings)
    - find all keys with a part in the middle (i.e. substrings)
    - find any string comparing at most N chars
    - find missing strings fast or faster
  - cons
    - hard to delete nodes
    - heavy memory use
    - not good with large keys (i.e. >= 10K char keys)
- misc
  - faster to delete a node then re-add it
- todos
  - [x] get the copy-pasted source code to compile and build
  - [x] type-copy the source code into `./modded`
  - [x] add code comments to `./modded`
  - [x] read text and add notes here
  - [x] watch video and add notes here

## Extra Credit

- [ ] ~~1. Implement a `TSTree_collect` that returns a `DArray` containing all of the keys that match the given prefix.~~
  - Skipped
- [ ] ~~2. Implement `TSTree_search_suffix` and a `TSTree_insert_suffix` so you can do suffix searches and inserts.~~
  - Skipped
- [ ] ~~3. Use the debugger to see how this structure is used in memory compared to the `BSTree` and `Hashmap`.~~
  - Skipped
