## To-Do

| Member                | Algorithm         |
| --------------------- | ----------------- |
| Arpit Jain            | Arithmetic Coding |
| Molshree Sharma       | Huffman           |
| Nishttha Saharkar     | Shannon Fano      |
| Simran Ahuja          | Fibonacci         |
| Yathansh Tewatia      | LZ77              |

***
## What To do
* All the algorithms are put in seperate files in the algorithms directory 
* Each file has a encode and decode function in them which are wrapped in their respective namespaces
* Encode function takes in raw text and encodes it according to the specified algorithm with all the information required to decode it (for example for huffman encoding store the probabilities of characters with the actual encoded message in the string returned from the encode function)
* decode function takes in an encoded string and returns the decoded string


***
## Needs Figuring Out
* How to write to a file in straight binary format rather than the normal utf-8/ascii
