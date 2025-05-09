import React from 'react';

const SocialMediaComponent = ({ links }) => {
  return (
    <div>
      <h2>Sosyal Medya</h2>
      <ul>
        {links.map((link, index) => (
          <li key={index}>
            <button onClick={() => window.open(link.url, '_blank')} type="button">
              <img src={link.icon} alt={link.name} />
            </button>
          </li>
        ))}
      </ul>
    </div>
  );
};

export default SocialMediaComponent;
