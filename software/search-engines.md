# Search
## 2.
Type vs. Token: type is like equiv. class of tokens
Gist: NL is messy
Stemming (approximate) vs. Lemmatization (complete vocab.) vs. Lemmatizer (NLP/morphological apprx.). Unfortunately, normalization helps some queries but hurts others, all-in-all it's unpredictable on performance.

### 2.3 Postings list intersection via skip pointers
Recall postings lists are sorted by terms, so we can use a skip list to do sub-linear intersection of two lists.
A good skip scheme is to have sqrt(length) equally space skip nodes, **not** the classic hierarchical approach.

### 2.4 Supporting phrase searches, i.e. "<term>" searches
##### Biword indices
Simple: Store bigrams and do a search for all phrase terms, overlapping with eachother.
You could then create a __biword index__
Better: do POS tagging and allow treat words like 'of', 'the', etc. as extended biwords.
Better: extend to longer sequences => __phrase index__
##### Positional indices
For each term, store postings of form `docID: <pos1, pos2, ...>` and record frequencies.
(41)

## [4. Index Construction](https://nlp.stanford.edu/IR-book/pdf/04const.pdf)
##### Blocked sort-based indexing
1. Read+parse as many documents into memory as possible into termID-docID pairs
2. Sort termID-docID pairs w/ termID as primary key
	4. Also collect all pairs by termID and aggregrate to 'postings list'. A posting is just a docID. Write this block of pairs+posting to disk.
5. External merge-sort the blocks, aggregrate the postings.

Downside: needs data structure for mapping terms to termIDs, which may not fit in memory!

Solution: single-pass in-memory indexing (SPIMI): it does not reduce terms to termIDs, but __creates a new dictionary per block.__

SPIMI is best with hashing dict, BSBI is usually a B-tree.

Main difference b/t SPIMI and BSBI:
	- BSBI: sort pairs, aggregrate postings by termID (easy, its sorted)
	- SPIMI: add each posting in an online manner. SPIMI __sorts terms **after** running out of memory & before writing to disk__. External merge-sort is still used.
So SPIMI modifies the local/block-writing aspect of BSBI.

**SPIMI allows compression.**

##### Distributed indexing w/ MR
	- Key partitions (termID ranges) are specified up-front
	- Each node assigned equal-sized splits of lists of documents
	- Each node does SPIMI on its split (but not the last merge step)
		- Parses
		- Map phase:    output (termID, docID) pairs
			- Each node sort's its local term list
			- Each node __stores local segment files__
		- Reduce phase: direct certain termIDs to certain nodes & aggregrate postings & store to disk
			- The nodes collection term partitions are called *inverters*, at the end they will sort all locally gathered pairs.
			- MR Master tells inverters locations of segment files to facilitate searching
	

##### Dynamic indexing
Simplest: re-index every once in a while.
Better: When new documents come in, add them to an auxiliary index (in memory) and search both indices. Merge later. Deletion by also maintaining status bit vector.

How to store postings?
	- Many files: allows easy appending, but too many files.
	- One huge file: Hard to update, but easier on OS.
	- Hybrid

Assume one large file for now.

Merging Aux + Stored Index:
	- Would be O(T^2 / n)
	- *Logarithmic merging*: O( T lg(T/n) )
		- Store log(T/n) indexes with sizes 2^i.
		- Put postings in Aux until no memory, push to new index, merge with last index, etc.
		- (Similar to *binomial heap*)	

(Postings list are sorted by docID, compression technique: store gaps, not absolute IDs) (But ranked search engines need sort by importance :(  )
