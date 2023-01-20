---
layout: post
title: Node Garbage Collector
description: >
  A clean approach to optimize Node Classes, by implementing the concept of Garbage Collectors in C++.
hide_image: false
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---

Hey lads, so I've been on working **Data Structures** for quite while & I created some **node structures** as **template classes** like, **Singly** & **Doubly linked-lists**, etc.

After playing with these structures, I realized that they perform some very expensive operations like **allocation** & **deallocation** of **nodes/memory**. Means each time when user decides to **push** or **pop** a **node**, the **compiler** makes request to **OS (Operating System)** for allocation/deallocation, which makes the process slower on the back-end.

Recently, I found out that <b>Java</b> has the concept of <a href="https://github.com/HypertextAssassin0273/Data_Structures_in_Cpp/blob/main/MY_DS_LIBRARY/Utilities/Garbage_Collector.hpp" target="_blank"><b>Garbage Collectors</b></a> for such scenarios. So, I thought why not implement in **C++**? And then, I added this really cool concept in my linked-list classes. Also, it's really powerful technique to boost your program for long run.

The working concept is simple. Each time we want to pop a node, we do not deallocate the node/memory. Instead we transfer it to a **static Garbage Collector**. So, later if someone wants to push a **new node**, we can reuse that transferred node from Garbage Collector. In this way, we don't have to deal with extra **OS requests** (i.e. using **new/delete** keywords).

But, here comes another problem, the program will gradually **increase in size** as its not releasing nodes/memory on the back-end. So I provided a **release method** for the user to have better control over **memory management**.

**Note:** In **Doubly linked list** class, this Garbage Collector works even more efficiently as each time a **class object** of a type gets destroyed, its' nodes are transferred to Garbage Collector at **O(1)** complexity, whereas in **Singly**, its **O(n)** if we are using standard implementation (i.e. having head pointer only), but if we use custom-heavy implementation (i.e. having tail pointer too), then its complexity will also become **O(1)**.

**P.S:** Below is the attached **source code folder link** for Singly & Doubly linked-list classes. If there is anything ambiguous, feel free to reach out. Peace!!!

<a href="https://github.com/HypertextAssassin0273/Data_Structures_in_Cpp/tree/main/MY_DS_LIBRARY/Linked_Lists" target="_blank"><b>Source Code Folder</b></a>
