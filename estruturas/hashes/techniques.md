# Closed Addressing/chaining/Open Hashing
## Reason for each name:
    - Closed Addressing -> The value will be **necessarily** stored at the index determined by the < hash > function.
    - Open Hashing -> Values are not stored directly at the index of the hash table, they are instead stored in `Buckets` .

# Open Addressing/Closed Hashing
## Reason for each name:
    - Open Addressing -> The value is **not necessarily** determined by the result of the `hash` function. If the index obtained is already taken, a new available index must be <probed>
    - Closed Hashing -> Values are stored directly at the index of the hash table, not using any other data structure
