---
layout: post
title: Animated PowerPoint Slides
image: /assets/img/mini-projects/ppt-slides.png 
caption: A collection of templates for unique slides
accent_color: '#4fb1ba'
accent_image:
  background: 'linear-gradient(to bottom,#193747 0%,#233e4c 30%,#3c929e 50%,#d5d5d4 70%,#cdccc8 100%)'
  overlay:    true
---

<body>
  <h4>Description:</h1>
  <p>Contains Latest Animated Presentations using Morph Transition & Zoom Feature, created on Microsoft PowerPoint 2019.</p>
  <a href="https://github.com/HypertextAssassin0273/Unique_PowerPoint_Presentations"><strong>GitHub Repo (Slides)</strong></a>  
  <div class="slideshow-container">
  
  <div class="mySlides fade">
    <div class="numbertext">1 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88329102-e616a200-cd42-11ea-9223-b63647a9dc77.jpg" style="width:100%">
    <div class="text">WELCOME SCREEN</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">2 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88329241-13635000-cd43-11ea-97e4-bffc401b2f1c.jpg" style="width:100%">
    <div class="text">MAIN MENU</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">3 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88329704-d481ca00-cd43-11ea-8421-320f6bd25395.jpg" style="width:100%">
    <div class="text">DICE MENU</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">4 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88329340-368dff80-cd43-11ea-84b0-060ebbdc37d8.jpg" style="width:100%">
    <div class="text">GAME BOARD & PLAYER STATS MENU</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">5 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88333127-1bbe8980-cd49-11ea-8250-0b0481ff61cd.jpg" style="width:100%">
    <div class="text">WIN MENU</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">6 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88329299-270eb680-cd43-11ea-9ef1-30311225b6cd.jpg" style="width:100%">
    <div class="text">LOAD GAME MENU</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">7 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88329541-8ec50180-cd43-11ea-8086-733ac5dc45a3.jpg" style="width:100%">
    <div class="text">SAVE GAME MENU</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">8 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88333274-604a2500-cd49-11ea-8ecc-502da434e9cd.jpg" style="width:100%">
    <div class="text">HIDDEN SETTINGS</div>
  </div>
  
  <div class="mySlides fade">
    <div class="numbertext">9 / 9</div>
    <img src="https://user-images.githubusercontent.com/66676402/88329383-4d345680-cd43-11ea-8990-4d2bd8c25164.jpg" style="width:100%">
    <div class="text">GUIDE MENU</div>
  </div>
  
  <a class="prev" onclick="plusSlides(-1)">&#10094;</a>
  <a class="next" onclick="plusSlides(1)">&#10095;</a>
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
