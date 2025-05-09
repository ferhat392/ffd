import React from 'react';

const ContactComponent = ({ contactInfo }) => {
  return (
    <div>
      <h2>İletişim</h2>
      <ul>
        {contactInfo.map((info, index) => (
          <li key={index}>
            <strong>{info.location}</strong>
            <p>{info.address}</p>
            <p>{info.phone}</p>
            <p>{info.email}</p>
          </li>
        ))}
      </ul>
    </div>
  );
};

export default ContactComponent;
