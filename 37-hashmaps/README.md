# Exercise 37: Hashmaps

## Notes

- code reviews
  - don't have to go from top to bot
  - are mentally taxing
  - tip: limit code reviews to 30 min max at a time
  - can use `cscope` and `grep` to help find all changes in code
- Zed's hashmap implementation notes
  - structure:
    ```
    Hashmap: {
      buckets: [
        bucket_1: [
          hashmapNode_1: {
            key: string
            data: string
            hash: integer
          }
        ],
        bucket_100: [ ... ]
      ],
      ...
    }
    ```
  - is a 100-sized array of arrays of `HashmapNode` structs
  - no checks for key collisions
  - no checks for unique keys / hashes
  - uses both a `HashmapNode`'s `key` and `hash` when getting a hashmap element's value (i.e. its `data`)
- misc
  - read Jon Bentley's 'Programming Pearls' books for more hashmap optimizations

## How To Improve It

- 6 improvements
- Skipped

## Extra Credit

- [ ] ~~1. Research the `Hashmap` implementation in your favorite programming language to see what features it has.~~
  - Skipped
- [ ] ~~2. Find out what the major disadvantages of a `Hashmap` are and how to avoid them. For example, it doesn't preserve order without special changes, nor does it work when you need to find things based on parts of keys.~~
  - Skipped
- [ ] ~~3. Write a unit test that demonstrates the defect of filling a `Hashmap` with keys that land in the same bucket, then test how this impacts performance. A good way to do this is to just reduce the number of buckets to something stupid, like five.~~
  - Skipped
