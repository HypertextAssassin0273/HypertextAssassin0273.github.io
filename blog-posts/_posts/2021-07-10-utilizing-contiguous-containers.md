---
layout: post
title: Utilizing STL Contiguous-Containers in a better way
description: >
  A very effective way to store a large amount of heavy-weight objects inside contiguous-containers in C++.
hide_image: false
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---

Containers like <a href="https://github.com/HypertextAssassin0273/Data_Structures_in_Cpp/blob/main/MY_DS_LIBRARY/Contiguous_Structures/Vector.hpp" target="_blank"><b>Vector</b></a> can't store a large amount of <b>heavy-weight</b> objects. They can either store a few heavy objects or a large amount of <b>light-weight</b> objects. A simple workaround for this problem is to use to <b>pointer-type</b> objects.
  
For instance, if we store 3 **integers** inside a vector, this will cost us 12 bytes. Similarly, if we have stored 3 **objects** of 10,000 bytes, this will reserve a total of 30,000 bytes inside vector. If we continue to allocate these heavy objects, soon we'll reach **limit** of that container and we'll no longer be able to allocate new objects  inside that container.

However, if we used pointer type to store these 3 objects inside the vector (using **new** keyword), this will only reserve 24 bytes inside vector (as each pointer costs us 8 bytes **irrespective of type**, so total 3x8=24 bytes), while additional 30,000 bytes in **heap-memory**. Now, we can easily store a large amount of these heavy-weight objects inside vector or any other **contiguous-container**.

This technique becomes very handy when you need to allocate heavy resources through contiguous-container in **large-scale** projects.

**Note:** Internally, vector allocates bytes by multiplying the **size of object-type** with **total no. of objects**.

**P.S:** If you have any ambiguity in understanding the concept, please watch this <a href="https://www.youtube.com/watch?v=j0_u26Vpb4w&t=1651s" target="_blank"><b>reference video</b></a>. Peace!
