---
layout: post
title: Optimized Minimal Custom Vector Class
description: >
  A minimal approach to create Optimized Custom Vector Class, covering 'Rule of Five' & implementing the concept of 'Mapping Objects on Dynamically Allocated Buffer'.
hide_image: false
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---

Hey Lads, so I've been working on Custom approach for improving & optimizing **STL::vector** (contiguous) container. Also recently, I shared 2 posts in this regard to improve Vector class by implementing **'Rule of Three' (covering copy- semantics)** & sharing an article to implement the [**'Rule of Five' (covering move- semantics)**](https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners).

Now, after implementing both of these Rules, I realized that still my Vector class was inefficient to carry out larger operations. So, I did my further research & found out that these Vectors basically work by separate **Allocation** & **Construction**. Yes, you heard it right. Allocation & Construction are 2 separate concepts which you normally implement both at same time by declaring object/array of objs with **'new/malloc'** keyword.

So, **STL::vector** initially only allocates & **reserves** the space for your objs & holds the **construction** part (i.e. you do this by using reserve func), and when user decides to use this space (i.e. by using push_back, emplace_back, resize, etc) the Vector Constructs the objs on that Dynamically allocated space (called **Buffer** on **Heap**).
Now, here comes the role of **'new placement operator'** which basically takes the address of buffer & constructs the object of given structure/class, etc on that position of buffer (i.e. we usually take array of **'char'** type to create buffer, ring any bells? well, some **Assembly** language concepts jumps out here).

After allocation & construction of these objs, comes the **accessing** part. Well, It was kind of tricky for me but I managed to find out (thanks to stackoverflow) that the objs created by **'new placement'** operator maintains like **'void'** type status. Means you can access them by type-casting the buffer-pointer to the type of objs & voila here you go, ready to use the Optimized Vector Class.

**P.S:** For better understanding, I have provided a lot of test-cases in attached [**Source code**](/assets/blog_material/Improved_Vector_Class.cpp) (which are also well-commented) & they almost cover all of the use-cases of my Custom Vector Class. If there is anything ambiguous, plz mention your problem in comments. I'll be really happy to help u guys out. Peace!!!

[**Link to Source code**](/assets/blog_material/Improved_Vector_Class.cpp)
