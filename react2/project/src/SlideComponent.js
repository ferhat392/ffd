import React, { useState, useEffect } from 'react';

const SlideComponent = ({ slides }) => {
  const [currentSlide, setCurrentSlide] = useState(0);

  useEffect(() => {
    const interval = setInterval(() => {
      setCurrentSlide((prevSlide) => (prevSlide + 1) % slides.length);
    }, 2000);

    return () => clearInterval(interval);
  }, [slides]);

  if (!slides || slides.length === 0) {
    return null;
  }

  return (
    <div>
      <h2>Slide</h2>
      <button onClick={() => setCurrentSlide((prevSlide) => (prevSlide - 1 + slides.length) % slides.length)} type="button">Previous</button>
      <img src={slides[currentSlide]} alt={`Slide ${currentSlide + 1}`} />
      <button onClick={() => setCurrentSlide((prevSlide) => (prevSlide + 1) % slides.length)} type="button">Next</button>
    </div>
  );
};

export default SlideComponent;
