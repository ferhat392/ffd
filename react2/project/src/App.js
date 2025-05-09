import React, { useState, useEffect } from 'react';
import SocialMediaComponent from './components/SocialMediaComponent';
import MenuComponent from './components/MenuComponent';
import SlideComponent from './components/SlideComponent';
import ContentComponent from './components/ContentComponent';
import ContactComponent from './components/ContactComponent';
import LanguageComponent from './components/LanguageComponent';

const App = () => {
  const [socialMediaLinks, setSocialMediaLinks] = useState([]);
  const [menuLinks, setMenuLinks] = useState([]);
  const [slides, setSlides] = useState([]);
  const [content, setContent] = useState([]);
  const [contactInfo, setContactInfo] = useState([]);
  const [languageData, setLanguageData] = useState({ tr: {}, en: {} });

  const [socialMediaVisible, setSocialMediaVisible] = useState(true);
  const [menuVisible, setMenuVisible] = useState(true);
  const [slideVisible, setSlideVisible] = useState(true);
  const [contentVisible, setContentVisible] = useState(true);
  const [contactVisible, setContactVisible] = useState(true);
  const [languageVisible, setLanguageVisible] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {

      } catch (error) {
        console.error('Veri çekme hatasi:', error);
      }
    };

    fetchData();
  }, []);

  return (
    <div>
      {/* Sosyal Medya */}
      {socialMediaVisible && (
        <div>
          <SocialMediaComponent links={socialMediaLinks} />
          <button onClick={() => setSocialMediaVisible(false)} type="button">Hide Social Media</button>
        </div>
      )}
      {!socialMediaVisible && <button onClick={() => setSocialMediaVisible(true)} type="button">Show Social Media</button>}

      {/* Menüler */}
      {menuVisible && (
        <div>
          <MenuComponent links={menuLinks} />
          <button onClick={() => setMenuVisible(false)} type="button">Hide Menu</button>
        </div>
      )}
      {!menuVisible && <button onClick={() => setMenuVisible(true)} type="button">Show Menu</button>}

      {/* Slide */}
      {slideVisible && (
        <div>
          <SlideComponent slides={slides} />
          <button onClick={() => setSlideVisible(false)} type="button">Hide Slide</button>
        </div>
      )}
      {!slideVisible && <button onClick={() => setSlideVisible(true)} type="button">Show Slide</button>}

      {/* İçerik */}
      {contentVisible && (
        <div>
          <ContentComponent content={content} />
          <button onClick={() => setContentVisible(false)} type="button">Hide Content</button>
        </div>
      )}
      {!contentVisible && <button onClick={() => setContentVisible(true)} type="button">Show Content</button>}

      {/* İletişim */}
      {contactVisible && (
        <div>
          <ContactComponent contactInfo={contactInfo} />
          <button onClick={() => setContactVisible(false)} type="button">Hide Contact</button>
        </div>
      )}
      {!contactVisible && <button onClick={() => setContactVisible(true)} type="button">Show Contact</button>}

      {/* Dil */}
      {languageVisible && (
        <div>
          <LanguageComponent data={languageData} />
          <button onClick={() => setLanguageVisible(false)} type="button">Hide Language</button>
        </div>
      )}
      {!languageVisible && <button onClick={() => setLanguageVisible(true)} type="button">Show Language</button>}
    </div>
  );
};

export default App;
