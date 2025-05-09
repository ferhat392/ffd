import React, { useState } from 'react';

const LanguageComponent = ({ data }) => {
  const [currentLanguage, setCurrentLanguage] = useState('tr');

  const handleChangeLanguage = (language) => {
    setCurrentLanguage(language);
  };

  return (
    <div>
      <h2>Dil Seçimi</h2>
      <div>
        <button onClick={() => handleChangeLanguage('tr')} type="button">Türkçe</button>
        <button onClick={() => handleChangeLanguage('en')} type="button">English</button>
      </div>
      <p>{data[currentLanguage].welcomeMessage}</p>
      <p>{data[currentLanguage].aboutMessage}</p>
    </div>
  );
};

export default LanguageComponent;
