---
layout: post
title: Forward_Deque
description: >
  A very unique approach to create a contiguous-container which basically overcomes all the reallocation problems in Vector Container in C++.
hide_image: false
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---

Hey lads, so today we're going to have an interesting discussion on a very unique structure. Recently, I was working on Vectors & unlike any other container, it has some cons, which I wanted to overcome by changing its internals. Thus, in process, I developed a new structure named as forward_deque. Now, before we dive into specifics of this stucture, its better to discuss the background & so, we'll start with the drawbacks of Vector Container.

Since, Vectors internally use a dynamically allocated array to store their elements, it performs reallocation process in order to grow in size when new elements are inserted. But, it also costs us two major issues:

1) invalidates pointers & references to elements (as they no longer point to stored elements at new memory addresses). Also, it makes Vector harder to be directly used as container for storing dependant resources in complex projects.
2) takes O(N) complexity of time to reallocate previously assigned resources (which isn't good performance wise when there are constant amount of push_backs & the capacity isn't reserved in Vector).

So, after alot of research, I found STL::Deque structure can overcomes these above stated issues. But the problem was that its current internal implementation is very heavy & costly as compare to the work we want to do as Vector Container. It's like killing a fly with nuke.
So, I came up with with a hybrid solution by simply taking the minimal approach of STL::Deque & named the structure as forward_deque (as it justifies the sense of one-sided deque since it only performs push_backs & pop_backs, similar to Vector).

The internal implementation of Forward_Deque is pretty simple. I've implemented it as Vector of vectors, making it same as dynamically allocated 2D array. As yet, if you recall the dynamic 2D arrays, they're simply dynamic array of pointers pointing to dynamic 1D arrays. Now, here comes the fun bit, storing your elements linearly in this specific composition gives you an advantage over the stored elements in Vector (or dynamic 1D array). The external pointers & references pointing to elements in 1D arrays are not invalidated on reallocation of main array of pointers. This gives us another advantage & overcomes our (2nd above stated) reallocation problem. The realloation process will give us Geometric (rather than Arithmetic) progression in terms of time complexity, if we ideally fixed the capacity of 1D array. To understand this, lets take an example in next paragraph.

Say, we fixed the capacity of chunk (1D array) as 8. On our first push_back, it will first alllocate a new chunk to main array of pointers and stores the provided element in 1st position of chunk. Afterwards, for rest 7 left positions in the chunk, it will directly place the elements one by one. Now, on inserting our 9th element, a reallocation in main array will occur & the 9th element will be stored in 1st position of newly allocated chunk & the next 7 elements will be stored directly in (current) 2nd chunk. But intriguingly, this reallocation in main array will not change the address of our previously stored elements in 1st chunk. Since, reallocation of main array will only copy pointer or base address of previous chunk. Hence, making the complexity time a Geometric progression which is way better than O(N) amount of time for reallocation.

**Note:** Use this container only in C++11 & higher versions as its performance heavily relies on "move semantics"

**P.S:** This implementation can easily become more memory-efficient by making it a "vector of fixed-size dynamic arrays" with only size attribute instead of taking "vector of vectors" as we don't need capacity attribute for our 1D Vector.
