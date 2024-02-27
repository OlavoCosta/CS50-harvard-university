// -------------------------- ANIMATIONS IMAGES -------------------------------------------

window.sr = ScrollReveal({ reset: true });

//  Homepage animation

sr.reveal('.hidden',{
    origin: 'right',
    distance: '-500px',
    duration: 1500,
    delay: 800,
});

sr.reveal('.emblem',{
    origin: 'top',
    distance: '300px',
    duration: 1000,
    delay: 200,
});

// ---------------------------------first Page animation------------------------------------

sr.reveal('.text-week1',{
    origin: 'left',
    distance: '300px',
    duration: 2000,
    delay: 100,
    easing: 'ease-in-out',
});

sr.reveal('.imgs01',{
    origin: 'right',
    distance: '150px',
    duration: 2000,
    delay: 300,
});

sr.reveal('.imgs02',{
    origin: 'bottom',
    distance: '300px',
    duration: 2000,
    delay: 100,
});

// ---------------------------------Second Page animation----------------------------------------

sr.reveal('.imgs03',{
    scale: 2,
    origin: 'left',
    distance: '150px',
    duration: 2000,
    delay: 300,
    easing: 'ease',
});

//--------------------------------------- Third Page animation----------------------------------

sr.reveal('.imgs04',{
    scale: 2,
    origin: 'left',
    distance: '300px',
    duration: 2000,
    delay: 200,
    easing: 'ease',
});

//--------------------------------------- Fourth Page animation----------------------------------

sr.reveal('.imgs06',{
    scale: 1,
    origin: 'top',
    distance: '100px',
    duration: 2000,
    delay: 200,
    easing: 'ease-in-out',
});

sr.reveal('.imgs07',{
    scale: 1,
    origin: 'left',
    distance: '100px',
    duration: 1000,
    delay: 200,
    easing: 'ease',
});

sr.reveal('.imgs08',{
    scale: 3,
    origin: 'bottom',
    distance: '100px',
    duration: 3000,
    delay: 300,
    easing: 'ease-in-out',
});

sr.reveal('.imgs09',{
    scale: 1,
    origin: 'bottom',
    distance: '100px',
    duration: 1000,
    delay: 800,
    easing: 'ease-in-out',
});

sr.reveal('.imgs10',{
    scale: 3,
    origin: 'right',
    distance: '100px',
    duration: 1000,
    delay: 200,
    easing: 'ease-in-out',
});

sr.reveal('.imgs11',{
    scale: 4,
    origin: 'bottom',
    distance: '200px',
    duration: 2000,
    delay: 300,
    easing: 'ease-in-out',
});

sr.reveal('.imgs12',{
    scale: 4,
    origin: 'right',
    distance: '300px',
    duration: 2000,
    delay: 800,
    easing: 'ease',
});

sr.reveal('.imgs13',{
    scale: 2,
    origin: 'left',
    distance: '200px',
    duration: 2000,
    delay: 100,
    easing: 'ease-in-out',
});

//--------------------------------------- Fifth Page animation----------------------------------

sr.reveal('.imgs16',{
    origin: 'top',
    distance: '200px',
    duration: 2000,
    delay: 100,
    easing: 'ease',
});

sr.reveal('.imgs17',{
    origin: 'top',
    distance: '200px',
    duration: 2000,
    delay: 800,
    easing: 'ease-in-out',
});

sr.reveal('.imgs18',{
    origin: 'top',
    distance: '200px',
    duration: 2000,
    delay: 1800,
    easing: 'ease-in-out',
});

//--------------------------------------- Sixth Page animation----------------------------------

sr.reveal('.imgs19',{
    origin: 'bottom',
    distance: '100px',
    duration: 2000,
    delay: 200,
    easing: 'ease-in-out',
});

//--------------------------------------- Final Page animation----------------------------------

sr.reveal('.strong2',{
    origin: 'bottom',
    distance: '400px',
    duration: 2000,
    delay: 1000,
    easing: 'ease-in-out',
});

// ------------------------ PAGE SECTION IMAGE C LANGUAGE --------------------------------------



// Get the DOM elements for the image carousel
const wrapper = document.querySelector(".wrapper"),
  carousel = document.querySelector(".carousel"),
  images = document.querySelectorAll("img"),
  buttons = document.querySelectorAll(".button");
let imageIndex = 1,
  intervalId;

// A function that updates the carousel display to show the specified image
const slideImage = () => {
    // Calculate the updated image index
    imageIndex = imageIndex === images.length ? 0 : imageIndex < 0 ? images.length - 1 : imageIndex;

    // Check if the value of `imageIndex * 100` is less than -800
    if (imageIndex * 100 < -800) {
      carousel.style.transform = `translate(-800%)`;
    } else {
      // Update the carousel display to show the specified image
      carousel.style.transform = `translate(-${imageIndex * 100}%)`;
    }
  };

// A function that updates the carousel display to show the next or previous image
const updateClick = (e) => {
    // Calculate the updated image index based on the button clicked
    imageIndex += e.target.id === "next" ? 1 : -1;

    // Check if the number of clicks is greater than 8
    if (imageIndex > 8) {
        imageIndex = 0;
    }
    // Check if the value of `imageIndex * 100` is less than -800
    if (imageIndex * 100 < -800) {
        carousel.style.transform = `translate(-800%)`;
    } else {
        slideImage(imageIndex);
    }
  };

// Add event listeners to the navigation buttons
buttons.forEach((button) => button.addEventListener("click", updateClick));
