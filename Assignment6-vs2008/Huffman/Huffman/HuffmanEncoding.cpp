/**********************************************************
 * File: HuffmanEncoding.cpp
 *
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 */

#include "HuffmanEncoding.h"
#include "HuffmanPQueue.h"
#include "error.h"
#include "queue.h"
#include <string>
#include <sstream>

//Helper functions

bool encodeChar(ext_char ch,Node* encodingTree,string& bits);

ext_char decodeChar(string bits,Node* encodingTree);

ext_char decodeCharRec(string bits,Node* encodingTree,int index);

Node* succinctDecodeTree(Queue<int>& struc, Queue<ext_char>& data);

void succinctEncodeTree(Node* root,Queue<int> &strucBits,Queue<ext_char> &data);

int charToInt(char ch);

char intToChar(int i);


/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */


Map<ext_char, int> getFrequencyTable(istream& file) {
	Map<ext_char, int> frequencies;
	frequencies.put(PSEUDO_EOF,1);
	while(true){
		ext_char ch= file.get();
		if(file.fail())break;
		//cout<<ch<<endl;
		if(frequencies.containsKey(ch)){
			frequencies[ch]++;
		}else{
			frequencies.put(ch,1);
		}
	}
	
	return frequencies;	
}

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
	Node* root;
	HuffmanPQueue hQueue;
	
	//enqueu all the frequencies
	foreach(ext_char key in frequencies){
		Node* newNode=new Node;
		newNode->character=key;
		newNode->weight=frequencies[key];
		newNode->one=NULL;
		newNode->zero=NULL;
		hQueue.enqueue(newNode);
	}
	
	//make a tree out of the queue
	while(hQueue.size()>1){
		Node* min1=hQueue.dequeueMin();
		Node* min2=hQueue.dequeueMin();
		Node* interiorNode=new Node;
		interiorNode->character=NOT_A_CHAR;
		interiorNode->weight=min1->weight+min2->weight;
		interiorNode->zero=min1;
		interiorNode->one=min2;
		hQueue.enqueue(interiorNode);
	}
	
	root=hQueue.dequeueMin();

	return root;
}

/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void freeTree(Node* root) {
	if(root!=NULL){
		freeTree(root->zero);
		freeTree(root->one);
		delete root;
	}
}

/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */ 

void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) {
	bool notFinish=true;
	while(notFinish){
		ext_char ch= infile.get();
		if(infile.fail()) {
			ch=PSEUDO_EOF;
			notFinish=false;
		}
		string bits;
		bool ans=encodeChar(ch,encodingTree,bits);
		if(!ans) error("char not defined in encoding tree");
		for(int i=0;i<bits.length();i++){
			int bit=charToInt(bits[i]);
			outfile.writeBit(bit);
		}
	}
	
}

/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */
void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
	string bits;
	while(true){
		int bit= infile.readBit();
		if(infile.fail()) break;
		bits+=intToChar(bit);
		ext_char ch=decodeChar(bits,encodingTree);
		if(ch==PSEUDO_EOF){
			return;
		}
		if(ch!=NOT_A_CHAR){
			bits="";
			file.put(char(ch));
		}
	}
}

/* Function: writeFileHeader
 * Usage: writeFileHeader(outfile, tree);
 * --------------------------------------------------------
 * Writes strucBits,bits representing structure of the
 * encoding tree, and data ,character present at each leaf node,
 * in the file. This information can thenbe used to 
 * decompress input files once they've been compressed.
 */
void writeFileHeader(obstream& outfile,Node* tree){
	Queue<int> strucBits;
	Queue<ext_char> data;
	succinctEncodeTree(tree,strucBits,data);

	int strucBitsSize=strucBits.size();
	int dataSize=data.size();

	outfile <<strucBitsSize<<' '<<dataSize<<' ';
	
	for(int i=0;i<strucBitsSize;i++){
		outfile.writeBit(strucBits.dequeue());
	}

	for(int i=0;i<dataSize;i++){
		outfile << data.dequeue() << ' ';
	}
}

//Using succinct structure instead

//void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
//	/* The format we will use is the following:
//	 *
//	 * First number: Total number of characters whose frequency is being
//	 *               encoded.
//	 * An appropriate number of pairs of the form [char][frequency][space],
//	 * encoding the number of occurrences.
//	 *
//	 * No information about PSEUDO_EOF is written, since the frequency is
//	 * always 1.
//	 */
//	 
//	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
//	if (!frequencies.containsKey(PSEUDO_EOF)) {
//		error("No PSEUDO_EOF defined.");
//	}
//	
//	/* Write how many encodings we're going to have.  Note the space after
//	 * this number to ensure that we can read it back correctly.
//	 */
//	outfile << frequencies.size() - 1 << ' ';
//	
//	/* Now, write the letter/frequency pairs. */
//	foreach (ext_char ch in frequencies) {
//		/* Skip PSEUDO_EOF if we see it. */
//		if (ch == PSEUDO_EOF) continue;
//		
//		/* Write out the letter and its frequency. */
//		outfile << char(ch) << frequencies[ch] << ' ';
//	}
//}

/* Function: readFileHeader
 * Usage: Node* encodingTree=reereadFileHeader(ibstream& infile);
 * --------------------------------------------------------
 * Reads the structure bits and data, and then calls 
 * helper function succinctEncodeTree to reconstruct the encoding Tree.
 */
Node* readFileHeader(ibstream& infile){
	Queue<int> strucBits;
	Queue<ext_char> data;
	
	int strucBitSize;
	infile>>strucBitSize;

	//skip the space.
	infile.get();

	int dataSize;
	infile>>dataSize;
	//skip the space.
	infile.get();
	
	for(int i=0;i<strucBitSize;i++){
		strucBits.enqueue(infile.readBit());
	}
		
	for(int i=0;i<dataSize;i++){
		int ch;
		infile>>ch;
		data.enqueue(ch);
		//skip the space.
		infile.get();
	}

	return succinctDecodeTree(strucBits,data);
}

//using succinct structure instead

//Map<ext_char, int> readFileHeader(ibstream& infile) {
//	/* This function inverts the mapping we wrote out in the
//	 * writeFileHeader function before.  If you make any
//	 * changes to that function, be sure to change this one
//	 * too!
//	 */
//	Map<ext_char, int> result;
//	
//	/* Read how many values we're going to read in. */
//	int numValues;
//	infile >> numValues;
//	
//	/* Skip trailing whitespace. */
//	infile.get();
//	
//	/* Read those values in. */
//	for (int i = 0; i < numValues; i++) {
//		/* Get the character we're going to read. */
//		ext_char ch = infile.get();
//		
//		/* Get the frequency. */
//		int frequency;
//		infile >> frequency;
//		
//		/* Skip the space character. */
//		infile.get();
//		
//		/* Add this to the encoding table. */
//		result[ch] = frequency;
//	}
//	
//	/* Add in 1 for PSEUDO_EOF. */
//	result[PSEUDO_EOF] = 1;
//	return result;
//}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void compress(ibstream& infile, obstream& outfile) {
	Map<ext_char,int> frequencies=getFrequencyTable(infile);
	Node* encodingTree=buildEncodingTree(frequencies);
	infile.rewind();
	writeFileHeader(outfile,encodingTree);
	encodeFile(infile,encodingTree,outfile);
	freeTree(encodingTree);
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void decompress(ibstream& infile, ostream & outfile) {
	Node* encodingTree=readFileHeader(infile);
	decodeFile(infile,encodingTree,outfile);
	freeTree(encodingTree);
}



//Helper Funtions


/* Function: encodeChar(ext_char ch,Node* encodingTree,string& bits)
 * Usage: encodeChar(char,encodingTree,bits);
 * --------------------------------------------------------
 * BackTracking fucntion to encode a character into 
 * bits(string passed by reference), using encoding tree.
 * Returns false if character is not defined in encoding tree.
 */
bool encodeChar(ext_char ch,Node* encodingTree,string& bits){
	if(encodingTree==NULL){
		return false;
	}else if(ch==encodingTree->character){
		return true;
	}else{
		for(int i=0;i<2;i++){
			if(i==0){	
				bits+="0";
				if(encodeChar(ch,encodingTree->zero,bits)){
					return true;
				}
				bits=bits.substr(0,bits.length()-1);
			}else{
				bits+="1";
				if(encodeChar(ch,encodingTree->one,bits)){
					return true;
				}
				bits=bits.substr(0,bits.length()-1);
			}
		}
		return false;
	}
}

/* Function: decodeChar(string bits,Node* encodingTree
 * Usage: ext_char ch = decodeChar(bits,encodingTree);
 * --------------------------------------------------------
 * Wrapper function to decodeCharRec, translates bits to character
 * using encoding tree, return NOT_A_CHAR if no such character is
 * defined in encoding tree.
 */

ext_char decodeChar(string bits,Node* encodingTree){
	ext_char ans=decodeCharRec(bits,encodingTree,0);
	return ans;
}

ext_char decodeCharRec(string bits,Node* encodingTree,int index){
	if(encodingTree==NULL || bits.length()==0){
		return NOT_A_CHAR;
	}else if(bits.length()==index){
		return encodingTree->character;
	}else{
		char ch=bits[index];
		int bitValue=int(ch) - 48;
		if(bitValue==0){
			return decodeCharRec(bits,encodingTree->zero,++index);
		}else{
			return decodeCharRec(bits,encodingTree->one,++index);
		}
	}
}


/* Function: succinctEncodeTree(Node* root,Queue<int> &strucBits,Queue<ext_char> &data)
 * Usage: succinctEncodeTree(root,struc,data);
 * --------------------------------------------------------
 * Encode tree into a struc bits and data queue (passed by refecence)
 * to write the encoding tree into the file later.
 */
void succinctEncodeTree(Node* root,Queue<int> &strucBits,Queue<ext_char> &data){
	if(root->zero == NULL && root->one == NULL){
		data.enqueue(root->character);
		strucBits.enqueue(0);
	}else{
		strucBits.enqueue(1);
		succinctEncodeTree(root->zero,strucBits,data);
		succinctEncodeTree(root->one,strucBits,data);
	}
}

/* Function: succinctDecodeTree(Queue<int>& struc, Queue<ext_char>& data)
 * Usage: Node* encodingTree = succinctDecodeTree(struc,data);
 * --------------------------------------------------------
 * Using structure bits and data constructs encoding tree
 * used to decompress file.
 */
Node* succinctDecodeTree(Queue<int>& struc, Queue<ext_char>& data){
	if(struc.isEmpty()) return NULL;
	int b = struc.dequeue();
	if(b== 0){
		ext_char key = data.dequeue();
		Node *root = new Node;
		root->character=key;
		root->zero = NULL;
        root->one = NULL;
		return root;
	}
    if(b == 1){
        Node *root = new Node;
		root->character=NOT_A_CHAR;
        root->zero = succinctDecodeTree(struc, data);
        root->one = succinctDecodeTree(struc, data);
        return root;
   }
   return NULL;
}

/* Function: charToInt
 * Usage: int num = intToChar('10');
 * --------------------------------------------------------
 * converts character to integer
 *i.e. return 10 for '10'
 */
int charToInt(char ch){
	return int(ch)- 48;
}

/* Function: intToChar
 * Usage: char ch = intToChar(10);
 * --------------------------------------------------------
 * converts integer to character
 *i.e. return '10' for 10
 */
char intToChar(int i){
	return char(i+48);
}