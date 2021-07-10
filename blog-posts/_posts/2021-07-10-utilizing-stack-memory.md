---
layout: post
title: Utilizing Stack Memory in a better way
description: >
  A very effective way to store a large amount of heavy-weight objects inside contiguous-containers in C++.
hide_image: false
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---

Containers like **vector** can't store a large amount of **heavy-weight** objects. They can either store a few heavy objects or a large amount of **light-weight** objects. A simple workaround for this problem is to use to **pointer-type** objects.

For instance, if we store 3 integers inside a vector, this will cost us 12 bytes. Similarly, if we have stored 3 objects of 10,000 bytes, this will reserve a total of 30,000 bytes of **stack-memory**.
If we continue to allocate these objects, soon we'll run out of stack-memory and we'll no longer be able to define new variables, objects, structs, classes, functions etc. on stack.

However, if we used pointer type to store these 3 objects inside the vector, this will only reserve 24 bytes in stack (as each pointer costs us 8 bytes, so total 3x8=24 bytes), while 30,000 bytes in **heap-memory**. Now, we can easily store a large amount of these heavy-weight objects inside vector or any other **contiguous-container**.

This technique is very effective specially when you have to be very careful of stack-memory in **large-scale** projects.

**P.S:** If you have any ambiguity in understanding the concept, please watch this [**reference video**](https://youtu.be/j0_u26Vpb4w?t=1651). Peace!
