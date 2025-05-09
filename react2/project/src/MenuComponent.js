import React from 'react';

const MenuComponent = ({ links }) => {
  return (
    <div>
      <h2>Menüler</h2>
      <ul>
        {links.map((link, index) => (
          <li key={index}>
            <button onClick={() => window.location.href = link.url} type="button">
              {link.label}
            </button>
          </li>
        ))}
      </ul>
    </div>
  );
};

export default MenuComponent;
