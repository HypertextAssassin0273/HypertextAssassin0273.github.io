---
layout: post
title: Optimized Minimal Custom Vector Container
description: >
  A minimal approach to create optimized Custom Vector Container in C++, covering 'Rule of Five' & implementing the concept of 'Mapping Objects on Dynamically Allocated Buffer'.
hide_image: false
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---

<body>
    <div>
        <p>
            Hey Lads, so I've been working on Custom approach for improving & optimizing the <b>STL::Vector</b> class as
            <b>contiguous container</b>. In this regard, I also recently shared two posts on our
            <a href="https://www.facebook.com/groups/450885176097764" target="_blank"><b>Facebook Group</b></a>
            for improving Vector class by implementing <a href="/assets/blog_material/Rule_of_Three.pdf"><b>Rule of
                    Three</b></a> (covering copy-semantics)
            & further <a href="https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners"
                target="_blank"><b>Rule of Five</b></a>
            (covering move-semantics).
        </p>
        <br>
        <p>
            Now, after implementing both of these Rules, I realized that still my Vector class was inefficient to carry
            out larger operations.
            So, I did my further research & found out that these Vectors basically work by separate <b>Allocation</b> &
            <b>Construction</b>.
            Yes, you heard it right. <b>Allocation</b> & <b>Construction</b> are two separate concepts which you
            normally implement both
            at same time by declaring <b>object</b> or <b>array of objects</b> with <b>'new/malloc'</b> keyword.
        </p>
        <br>
        <p>
            So, <b>STL::Vector</b> initially only allocates & <b>reserves</b> the space for your objects & holds the
            construction part
            (i.e. you do this by using reserve <b>modifier</b>), and when user decides to use this space
            (i.e. by using push_back, emplace_back or resize modifier), the Vector constructs the objects on that
            <b>dynamically</b>
            allocated space (called <b>Buffer</b> on <b>Heap</b>).
        </p>
        <br>
        <p>
            Now, here comes the role of <a href="https://www.geeksforgeeks.org/placement-new-operator-cpp"
                target="_blank"><b>placement new</b></a>
            operator which basically takes the <b>address of buffer</b> & constructs the object of given structure or
            class on that position of buffer
            (i.e. we usually take <b>array of char</b> type to create buffer).
        </p>
        <br>
        <p>
            After allocation & construction of these objects, comes the <b>accessing</b> part. Well, It was kind of
            tricky for me
            but I managed to find out (thanks to stackoverflow) that the objects created by <b>placement new</b>
            operator maintains
            like <b>void</b> type status. Means you can access them by <b>type-casting</b> the <b>buffer-pointer</b> to
            the type of
            <b>objects</b> & voila, you are ready to use the optimized Vector class.
        </p>
        <br>
        <p>
            <b>P.S:</b> For better understanding, I have provided a lot of <b>test-cases</b> seperately in below
            attached <b>Source Code Folder</b>
            (which are also well-commented) & they almost cover all of the use-cases of my custom Vector class.
            Also, I have used an <a href="https://tristanbrindle.com/posts/beware-copies-initializer-list"
                target="_blank"><b>Instance-Counter</b></a>
            class in some test-cases to keep the track of Constructions & Destructions of objects in Vector class.
            If there is anything ambiguous, feel free to reach out. Peace!!!
        </p>
        <br>
        <a href="https://github.com/HypertextAssassin0273/Data_Structures_in_Cpp/tree/main/Native_Data_Structures/Contiguous_Structures"
            target="_blank"><b>Source Code Folder</b></a>
    </div>
</body>
