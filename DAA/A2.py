import heapq  # Import the heapq module for the priority queue
from collections import defaultdict  # Import defaultdict to count character frequencies

# Function to build the Huffman tree
def buildHuffmanTree(text):
    char_freq = defaultdict(int)  # Create a dictionary to store character frequencies

    # Calculate the frequency of each character in the input text
    for char in text:
        char_freq[char] += 1

    # Create a priority queue to store the Huffman nodes
    heap = [[weight, [char, ""]] for char, weight in char_freq.items()]  # Create a list of nodes (initially, one for each character)
    heapq.heapify(heap)  # Convert the list into a min-heap

    while len(heap) > 1:
        lo = heapq.heappop(heap)  # Pop the node with the lowest weight
        hi = heapq.heappop(heap)  # Pop the node with the second lowest weight
        for pair in lo[1:]:
            pair[1] = '0' + pair[1]  # Append '0' to the codes of characters in the left branch
        for pair in hi[1:]:
            pair[1] = '1' + pair[1]  # Append '1' to the codes of characters in the right branch
        heapq.heappush(heap, [lo[0] + hi[0]] + lo[1:] + hi[1:])  # Combine the nodes and push the result back into the heap

    return sorted(heap[0][1:], key=lambda p: (len(p[-1]), p))  # Return the sorted list of character-code pairs

# Function to encode text using Huffman codes
def huffmanEncode(text):
    huffman_tree = buildHuffmanTree(text)  # Build the Huffman tree
    huffman_codes = dict(huffman_tree)  # Convert the tree into a dictionary for easy lookup
    encoded_text = ''.join(huffman_codes[char] for char in text)  # Encode the input text using Huffman codes
    return encoded_text  # Return the encoded text

# Function to decode Huffman-encoded text
def huffmanDecode(encoded_text, huffman_tree):
    decoded_text = ''
    while encoded_text:
        for char, code in huffman_tree:
            if encoded_text.startswith(code):  # Check if the encoded text starts with a Huffman code
                decoded_text += char  # Append the corresponding character to the decoded text
                encoded_text = encoded_text[len(code):]  # Remove the matched code from the beginning of the encoded text
                break
    return decoded_text  # Return the decoded text

if __name__ == "__main__":
    input_text = "simple example for huffman encoding"
    
    # Encode the input text using Huffman codes
    encoded_text = huffmanEncode(input_text)
    
    # Print Huffman codes in the format "letter: Huffman code"
    huffman_tree = buildHuffmanTree(input_text)
    huffman_codes = dict(huffman_tree)
    print("\nLetter : HuffmanCode\n")
    for char, code in sorted(huffman_codes.items()):
        print(f"{char} : {code}")

    # Decode the encoded text
    decoded_text = huffmanDecode(encoded_text, huffman_tree)
    
    print("\nOriginal Text:", input_text)
    print("\nEncoded Text:", encoded_text)
    print("\nDecoded Text:", decoded_text)
