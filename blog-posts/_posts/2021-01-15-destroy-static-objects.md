---
layout: post
title: Deallocate/Destroy Static Variables & Objects
description: >
  A simple technique to manually deallocate/destroy static variables & objects.
hide_image: false
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---

We all know how **Dynamic** variables or objects work & can be destroyed after utilizing them (i.e. by using **delete** keyword). But ever wondered how **static** (normal) variables or objects can be destroyed after utilizing them?

Well it's simple. Since, their **life-span** depends on the **scope**. So, you can define them inside that scope (i.e. by simply using a **pair of parenthesis**) & they will be destroyed after the program jumps out of that scope.

This technique comes very handy when your program contains too many static variables & their use is very short in the entire program.

**P.S:** Attached [**Source Code**](/assets/blog_material/Static_Obj_Manual_Destruction.cpp) is an example which elaborates this more deeply. Run its **.exe** file & then compare the output with code to understand thoroughly. Hope u guys will like it. Peace!!!

[**Source Code Link**](/assets/blog_material/Static_Obj_Manual_Destruction.cpp)
