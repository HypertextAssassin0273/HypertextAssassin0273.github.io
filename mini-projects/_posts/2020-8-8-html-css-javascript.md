---
layout: post
title: HTML-CSS-JavaScript Web Apps
image: /assets/img/mini-projects/html-css-javascript.gif
caption: A collection of HTML-CSS-JavaScript based Web Programs
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
  <p>The main purpose of this project is to understand the synergy b/w html,css & javascript on github pages. Moreover, it includes CSS-Grids & JavaScript Frameworks too.</p>
  <a href="https://hypertextassassin0273.github.io/html-css-javascript" target="_blank"><strong>Website Page</strong></a> &nbsp;
  <a href="https://github.com/HypertextAssassin0273/html-css-javascript" target="_blank"><strong>GitHub Repo</strong></a>
  <br>
  <h2 style="text-align: center;">Slideshow Gallery</h2>
  <div class="slideshow-container">
  
  <div class="mySlides fade">
    <div class="numbertext">1 / 3</div>
    <img src="/assets/img/mini-projects/slideshow/hmtl-css-javascript-exp-1.gif" style="width:100%">
    <div class="text">Arithmetic Calculator</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">2 / 3</div>
    <img src="/assets/img/mini-projects/slideshow/hmtl-css-javascript-exp-2.gif" style="width:100%">
    <div class="text">Flappy Bug Game</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">3 / 3</div>
    <img src="/assets/img/mini-projects/slideshow/hmtl-css-javascript-exp-3.gif" style="width:100%">
    <div class="text">Rigley Escape Game</div>
  </div>
  
  <a style="border-bottom: none;" class="prev" onclick="plusSlides(-1)">&#10094;</a>
  <a style="border-bottom: none;" class="next" onclick="plusSlides(1)">&#10095;</a>
  </div>
  <br>
  
  <div style="text-align:center">
    <span class="dot" onclick="currentSlide(1)"></span> 
    <span class="dot" onclick="currentSlide(2)"></span> 
    <span class="dot" onclick="currentSlide(3)"></span>
  </div>

  <script>
    {% include scripts/slideshow.js %}
  </script>
</body>
