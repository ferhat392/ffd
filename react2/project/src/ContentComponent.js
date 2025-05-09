import React from 'react';

const ContentComponent = ({ content }) => {
  return (
    <div>
      <h2>İçerik</h2>
      <div>
        {content.map((item, index) => (
          <div key={index}>
            <h3>{item.title}</h3>
            <p>{item.description}</p>
          </div>
        ))}
      </div>
    </div>
  );
};

export default ContentComponent;
