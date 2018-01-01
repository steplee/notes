# [Online book](https://web.stanford.edu/~jurafsky/slp3/)
## 4.
**Perplexity** is geometric mean of inverse probability.
(In case of a Markov model, it factorizes to product of sequence given last word)
#### n-grams
Model language by `p(y|x) = #{y follows x} / #{x}`
Longer markov chains (i.e. `n` > 1) factorize by **chain rule of probability**.
The counting process corresponds to MLE
#### Smoothing (discounting)
If training corpus never sees y follow x, we assign 0 probability.
Add `1` or `k` to both numerator and `k*V` to denom (`V` is vocab size).
For better MLE interpretation: define **adjusted count** `c' = (c+1)(N/(N+V))`
Another interpretation is by **discount** `d = c' / c`

`k` may be chosen with a devset, usually one-smoothing is used though.

**Backoff**: Store n-grams of different lengths, if as query n-gram doesn't exist, try the (n-1)-gram (or if we don't have enough evidence to believe the higher gram).

**Interpolation**: Weigh n-grams for several n and combine to estimate the full n-gram

n-grams with greater `n` are more likely to occur again. Think about this!
**Absolute discounting**: subtract a fixed amount `d` from each count.
> The intuition is that since we have good estimates already for the very high counts, asmall discount d wont affect them much. It will mainly modify the smaller counts, for which we dont necessarily trust the estimate anyway

**Kneser-Ney**: absolute discounting with more sophisicated lower-order unigram distribution estimation.
Essentially, we want to model if words are appropriate for *'novel continuations'*, for example *glass* is more likely to follow in a never-seen-before context then is *Kong*, even though *Kong* may be a more frequent unigram. So Kneser-Ney __counts the number of different contexts a word has appeared in, that is how many bigrams it completes__. The prob of a word being a continuation is `#{bigrams completed by w} / #{total bigrams}`
Now when predicting a never-seen-before bigram, add a weighted factor of p_continuation to normal prediction (The weighting has a formula, see text).

#### Perplexity & Entropy
Cross-Entropy `H(p,m) = - sum[p logm]` is an upper-bound on Entropy: `H(p) <= H(p,m)`
(It is actually only defined when sequence is inifinite)
__The difference between ent and xent is a measure of a models accuracy__.
__for two models m1 and m2, the better one is the one with smaller difference of `H(p)` and `H(p,.)`__.
A model's output over a finite sequence can be used as an approximation to (infinite) xent. It's **exponential is the perplexity**.

## 5. Noisy Channel
This chapter contains some interesting methods of detecting typing errors, spelling by pronunciation, and an introduction to bayesian inference.

Two kinds of spelling correction: (non-word: transform from non-word to actual word) and (word: transform from one mispelled but actual word to another)
Noisy Channel Model can apply to both, though moreso for the first.

##### Non-word Errors
The philosophy of the NC model is to infer the correct word given a noisy message. Following Bayesian inference we construct a conditional given the message and pick the argmax. We actually do use Bayes rule in this case, we model the probability of `noisy message x | true word w` not `true w | message x`, and apply Bayes conjugation (though denominator will cancel out anyways).
The relevant formula is: $\hat{w}\ =\ argmax_w P(x | w) P(w)$
Clearly, we need a *prior* and a *likelihood model*, the channel model.
The prior could be unigram or n-gram.
The channel model has many design choices.
  - We probably should use something based on edit-distance (including transpositions)
  - We should probably put more mass on deletions and transpositions then insertions
  - One technique is to examine a corpus for single-character mistakes and build a **confusion matrix** to indicate which characters are mistook for others.
    - An interesting way to compute the matrices are by iteration: initially each has error has the same weight, by making multiple passes we refine our weightings. This is an instance of EM!

##### Real-word Errors
We will run a corrector on each word independently.
Model three things:
  1. probability user makes an error for any given word ($1\ -\ \alpha$)
  2. channel model
  3. prior on all nearby (low edit-distance) words (eg. unigram or n-gram)
Then select the argmax of these the product of these three factors.
Note: we need classes of nearby words to cut down search space (and retain numerical precision when normalizing)
Real systems need to account for proper names, 'blacklists' (eg. never change numbers or names), requiring a certain margin of higher probability

###### Modelling Partitions & Pronunciation
See 'Bill and Moore 200'.
They propose to model errors after a typist chooses a word, then a partition. For example, they type physical by segmenting `ph y s i c al` but mispell `ph` as `f`. Then model local edits as $p(\text{f} | \text{ph})$, and the entire spelling as the product of the partitions. You can also add the place of the parition into the conditional. Align the true/model paritions by trying all and taking argmax.

GNU aspell has a more sophistcated approach by accounting for pronunciation with common rules

## 6. NB & Sentiment
Here, 'True/False' means actual, 'Pos/Neg' means what we labelled.
**Precision** = `TruePos / (TruePos + FalsePos)`
**Recall**    = `TruePos / (TruePos + FalseNeg)`
Precision: % detected correctly
Recall:    % detected at all

**F-measure** = $\frac{(\Beta^2 + 1)\ PR}{\Beta^2P\ +\ R}$

For $\Beta$ > 1, we favor recall.
For $\Beta$ < 1, we favor precision.
**$F_1$** is very common.
F-measures are related to the harmonic mean.
> Harmonic mean is used because it is a conservative metric; the harmonic mean of two values is closer to the minimum of the two values than the arithmetic mean is. Thus it weighs the lower of the two numbers more heavily.

## 7. (2nd Edition!) Phonetics
Phonology: idea that words are composed of smaller units of speech.
Phonetics: the study of linguistic sounds and their production.
Phones/Segments: the basic units.
Articulatory phonetics (production), acoustic phonetics (analysis of waveforms), phonology (systematic study of sound structures).
#### Articulatory Phonetics
Expel air through windpipe (trachea). As it passes through the trachea, passes through larynx (Adam's apple, voice-box). Larynx has two folds of muscle (vocal folds), which can move together or apart (the space between is the glottis). If the folds are close, the air will vibrate, otherwise it won't. Vibrations produce __voiced sounds__ (b/d/g/v/z/...), when the folds are apart __unvoiced sounds__ (p/t/k/f/s/...) are produced.
The area above trachea is the vocal tract, contains oral and nasal tracts. Air may pass through either, though more pass through the mouth.
##### Consonants
Always result from blocked airflow, may be voiced or unvoiced.
The __place of articulation__ is the point where most of the blocking of air is done, and a great way to classify consonants. Could be (labial: lips), (dental: teeth), (alveolar: roof of mouth), (palatal: tongue to roof), (velar: roof muscle), (glottal: closing glottis)
The __manner of articulation__ is also important, ie. a complete/partial/length of stoppage of air.
  - A *stop* completely blocks air (closure) and 'explodes' (release)
  - Nasal sounds lower velum and force air into nasal cavity
  - *Fricatives* constrict air but allow passage to make a turbulent 'hissing' sound.
  - *Sibilants* are high-pitched fricatives.
  - *Affricates* are __stops followed immediately by fricatives__ (eg. [ch] in 'chicken')
  - *Approximants* are less turbulent then fricatvies ([y] in yellow)
  - *Tap/Flap* is a quick motion of tongue to the roof of mouth

##### Vowels 
Less obstructed air, usually voiced and louder.
Important parameters are:
  - Height (height of highest point of tongue)
  - Front/Backness (highest point of tongue)
  - Roundness (shape of lips)
A *dipthoing* is a vowel that has the tongue move forward or backward during articulation (important in English).

#### Syllables
Combination of vowels and consontants. No standard definition.
Core vowel: __nucleus__
Optional leading consonants: __onset__
Onset with multiple consontants: __complex onset__
Following consonants: __coda__
Nucleus + coda: __rime__
consider 'green': `(gr) (iy n)` which is `(onset) (nucleus coda)`
English restricts certain onsets, allowing supervised model fitting and generation of allowable new words.
When English speakers want to stress a word, their are definite syllables (__lexical stress__) that they will accent.
Unstressed vowels can be further weakend to __reduced vowels__ like the __schwa__.
__Prominence__, the accentation, stressing, weakening of vowels, etc., is actually a continuum so no hope in codifying it all.

### Phonological Variation
> The [t] of tunafish is aspirated. __Aspiration__ is a period of voicelessness after a stop closure and before the onset of voicing of the following vowel. Since the vocal cords are not vibrating, aspiration sounds like a puff of air after the [t] and before the vowel. By contrast, a Unaspirated [t] following an initial [s] is unaspirated; thus the [t] in starfish ([s t aa r f ih sh]) has no period of voicelessness after the [t] closure

Deal with the incredible variation of speech by assuming speakers focus on abstrct categories, not details.
**Phoneme**: simplest abstract class. (denoted `/xxx/`)
**Allophone**: the actual realizations of phonemes, with variance.
**Reduction/Hypoarticulation**: when a native speaker blurs sounds.
**Coarticulation**: changing articulators (vocal folds) in anticipation of next sounds.
It is useful to label sounds with **distinctive features** which are binary variables that help infer intent/feeling/etc. Denoted eg. `[+dorsal]`
Can try to model variation with phonological rules (Chomsky), but misses a lot.
Speakers delete sounds more when the following word is predictable!

### Acoustics
Clearly, ampltitutde represents air pressure, 'loudness' is less easy :)
The frequency of a sound comes from the speed of vibration of vocal folds, and is the fundamental frequence ($F_0$). A pitch-track graph plots the $F_0$ over time. You also want to look at signal power (mean-square) over a window.
pitch ~ frequency, loudness ~ power.
Extracting pitch is not trivial however, usually do an autocorr.
> It turns out that these spectral peaks that are easily visible in a spectrum are very characteristic of different phones; phones have characteristic spectral signatures. Just as chemical elements give off different wavelengths of light when they burn, allowing us to detect elements in stars looking at the spectrum of the light, we can detect the characteristic signature of the different phones by looking at the spectrum of a waveform. This use of spectral information is essential to both human and machine speech recognition. In human audition, the function of the cochlea or inner ear is to compute a spectrum of the incoming waveform. Similarly, the various kinds of acoustic features used in speech recognition as the HMM observation are all different representations of spectral.

In spectograms (short-time dfts) dark bars emerge seperated in time (**formants**) and usually represent differnt vowels.

(TODO: continue at 7.4.5)


## 21. Information Extraction
Turn unstructured data into structured data.
First step: **name entities**. The entities are application specific (people, places, dates,...)
We may also want to:
  - **resolve coreferences**, e.g. as the first step of clustering or indexing.
  - **extract relations** 
  - **extract events** 
  - **extract coreferences**, to find out which events refer to the same event.
  - **recognize temporal expressions** and then **normalize** them to some canonical form.
  - **template fill**

### Named Entity Resolution (NER)
An entity is anything that can referred to with a proper name, though usually application specific, but also dates, times, etc.
**Word-shape** forgets characters but retains capitazliation and letter vs. number spots.

#### Practical Considerations
Typical systems make multiple passes to build rules, as well as hand-written rules.
A single pass may carry out the following steps:
  1. Use high-preceision rules to tag unambiguous entities.
  2. Search substring matches of previous names
  3. Consult tables/lists (given) to identify likely entity mentions
  4. Apply probablistic sequence labelling to use tags from previous stages as additional features.
This does a number of things, including allowing shortened names (mentioned after a full length introduction) to be coreferred.

### Relation Extraction
Model things such as `part-of`, `disrupts`, `causes`, `location-of`, etc.
  - Can do by regex or parsing pretty effectively, but with low recall.
  - Supervised works better, but must label a corpus AND fix classes of entities. First NER is done, then classifiers are run pairwise to determine which entities are related, then another classifier is used to determine which entity. An advanced classifier may use **syntactic paths**, running the classifier on the sequence of nodes from one word to another in the parsed tree.
  - Semi-supervised by having a few high-precision *seed patterns* or *seed tuples* allow bootstrapping by finding all sentecnes that contain the entities and __extracting and generalizing the context around them to learn new patterns__. We would find the pair of entities, capture all perhaps interior words, punctuation, adpositions, etc. and search for these structures to find __other__ entities. We can even prevent __semantic drift__ by assigning confidence values. We can use the confidence measures, `hits` and `finds`, to assess evidence of new tuple/relations and use the **noisy-or** model to accept/reject them.
    - In noisy-or, for a tuple to be false, *all* of its supporting patterns must have been in error AND the sources of their individual failures are independent. So the probability that *all* of them are wrong is $1\ -\ \prod{confidence(p_i)}$

  - Distant Supervision: TODO


## 28. Question Answering
Two kinds: IR-based & Knowledge-based
Also hybrid.
### IR-based
	1. Process question to determine **answer type**, usually a *named entity*.
	2. Determine query to search for.
	3. Use search engine techniques to rank documents.
	4. Extract meaningful document pieces and rerank.
	5. Return ranked pieces.

#### Query Processing
Extract pieces of info from question.
Possibly extract *focus*, the expected string of words that will be _replaced_ by the found answer.
Possibly classify *question type*, which may be helpful to determine *answer type*.
Classify *answer type*, which cuts search space and restricts to certain named entities, or use a fully hiearchical _answer type taxonomy_ with specific classes.
> Most modern question classifiers, however, are based on supervised machine learning, and are trained on databases of questions that have been hand-labeled with an answer type (Li and Roth, 2002). Typical features used for classification include the words in the questions, the part-of-speech of each word, and named entities in the questions. Often, a single word in the question gives extra information about the answer type, and its identity is used as a feature. This word is sometimes called the answer type word or question headword, and may be defined as the headword of the first NP after the questions wh-word.

#### Query Formulation
Decide which words to remove/add.
**Query Reformulation**: `when was the laser invented` -> `the laser was invented`. This would hopefully turn a match in a search engine.
#### Passage Retrieval
Query the search engine, extract useful passages, rank these passages. Use the _answer type_ to filter out passages.
The final ranking is usually done via supervised ml, features could be number of named enitites, question keywords, proximity of keywords to eachother in the passage, N-gram overlap b/t question and answers, etc.
#### Answer Processing
Extract exact answer from passage. Two approaches: answer-type **pattern extraction** and **N-gram tiling**.
1. Pattern Extraction: Using the expected answer-type, try to search the passage using regexps dependent on the answer-type. Rather than simple regexs, could do rank again all candidate answers using supervised ml with some nifty features.
2. Really only useful for search engines. Use answer-type to score all n-grams in all passages, concatenate the overlapping n-grams to full answer.


### Knowledge-based
Build semantic representation of query., e.g. Prolog style with hard logic constraints.
Could also convert to any kind of structured query, e.g. SQL or lisp.
Mapping a string to any logical form is called semantic parsing.
**RDF Triples**: a basic structured database for `subject - predicate - object` data.

#### Rule-based Methods
Hand write rules for common queries.
If you have supervised data for questions to logical form of the answer, you usually (parse questions) then (align parse trees to wanted logical form).
More complex queries need to be parsed and transformed to a logical form (think of transformers from the compiler book), see [this paper](https://homes.cs.washington.edu/~lsz/papers/zc-uai05.pdf) TODO.
#### Semi-supervised Learning
We need this to scale. With redundancy, we can learn to generalize our labelled dataset. See 'distant supervising' and 'open info extraction' from Chapter 20. E.g. using wikipedia, we can learn the form of some predicate relation and capture other instances of it, called 'aligning'.
Paraphrase corpi are useful for aligning questions.
#### IBM Watson DeepQA
1. Question processing
  - extract focus, answer-type, question classification, question sectioning
  - focus should co-refer with answer, it will help filter passages.
  - deepqa does less filtering then you may expect and relies on ranking and computing power.
2. ... todo


