---
layout: post
title: Animated PowerPoint Slides
image: /assets/img/mini-projects/ppt-slides.png 
caption: A collection of unique slides templates
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---
<head>
  <style>
    {% include styles/slideshow.scss %}
  </style>  
</head>  
<body>
  <h4>Description:</h4>
  <p>Contains Latest Animated Presentations using Morph Transition & Zoom Feature, created on Microsoft PowerPoint 2019.</p>
  <a href="https://github.com/HypertextAssassin0273/Unique_PowerPoint_Presentations" target="_blank"><strong>GitHub Repo (Slides)</strong></a>
  <br>
  <h2 style="text-align: center;">Slideshow Gallery</h2>
  <div class="slideshow-container">
  
  <div class="mySlides fade">
    <div class="numbertext">1 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-1.png" style="width:100%">
    <div class="text">iSlide Add-In</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">2 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-2.gif" style="width:100%">
    <div class="text">Carousel Effect</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">3 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-3.gif" style="width:100%">
    <div class="text">Zoom Feature</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">4 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-4.gif" style="width:100%">
    <div class="text">Prezi Style-1</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">5 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-5.gif" style="width:100%">
    <div class="text">Animated Carousel Agenda</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">6 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-6.gif" style="width:100%">
    <div class="text">Multiple Slides Parallax Effect</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">7 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-7.gif" style="width:100%">
    <div class="text">Animated Business Report</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">8 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-8.gif" style="width:100%">
    <div class="text">Parallex Effect</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">9 / 9</div>
    <img src="/assets/img/mini-projects/slideshow/ppt-exp-9.gif" style="width:100%">
    <div class="text">Prezi Style-2</div>
  </div>
  
  <a style="border-bottom: none;" class="prev" onclick="plusSlides(-1)">&#10094;</a>
  <a style="border-bottom: none;" class="next" onclick="plusSlides(1)">&#10095;</a>
  </div>
  <br>
  
  <div style="text-align:center">
    <span class="dot" onclick="currentSlide(1)"></span> 
    <span class="dot" onclick="currentSlide(2)"></span> 
    <span class="dot" onclick="currentSlide(3)"></span>
    <span class="dot" onclick="currentSlide(4)"></span> 
    <span class="dot" onclick="currentSlide(5)"></span> 
    <span class="dot" onclick="currentSlide(6)"></span>
    <span class="dot" onclick="currentSlide(7)"></span> 
    <span class="dot" onclick="currentSlide(8)"></span>
    <span class="dot" onclick="currentSlide(9)"></span>
  </div>

  <script>
    {% include scripts/slideshow.js %}
  </script>
</body>
