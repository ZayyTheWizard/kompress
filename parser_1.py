import sys
import json
from heapq import heappop, heappush

class Node:
    def __init__(self, char=None, freq=None, left=None, right=None):
        self.char = char
        self.freq = freq
        self.left = left
        self.right = right

    def is_leaf(self):
        return self.left is None and self.right is None

def rebuild_huffman(json_data):
    data = json.loads(json_data)
    root = None
    if data['type'] == 'huffman tree':
        root = build_tree(data['root'])
    return root

def build_tree(node_data):
    char = node_data['char']
    freq = int(node_data['freq'])
    if char == '$':
        left = build_tree(node_data['left'])
        right = build_tree(node_data['right'])
        return Node(char='$', freq=freq, left=left, right=right)
    else:
        return Node(char=char, freq=freq)

def serialize_tree(node):
    if node is None:
        return None
    if node.char == '$':
        return {'char': '$', 'freq': node.freq, 'left': serialize_tree(node.left), 'right': serialize_tree(node.right)}
    else:
        return {'char': node.char, 'freq': node.freq}

def EncodedMessage(jsonS):
    data = json.loads(jsonS)

    return data.get('message')


def retString(json_data):
    root = rebuild_huffman(json_data)
    decodedMessage = decode_message(json_data, root)

    return decodedMessage

def decode_message(json_data, root):
    # Example logic to decode the message using the Huffman tree
    encoded_message = EncodedMessage(json_data)
    decoded_message = ""
    current_node = root
    
    for bit in encoded_message:
        if bit == '0':
            current_node = current_node.left
        else:
            current_node = current_node.right
        
        if current_node.is_leaf():
            decoded_message += current_node.char
            current_node = root  # Reset to root for next character
    
    return decoded_message

if __name__ == '__main__':
    decodeMessage = retString(sys.argv[1])

    decodeMessage = decodeMessage.replace("_", " ")

    print(decodeMessage)
