import React from 'react';

const ClassComponent = ({ data }) => {
  return (
    <div>
      <h3>{data.className}</h3>
      <p>Kat: {data.floor}</p>
      <p>Sira Sayisi: {data.seatCount}</p>
      <p>Bilgisayar: {data.hasComputer ? 'Evet' : 'Hayir'}</p>
      <p>Beyaz Tahta: {data.hasWhiteboard ? 'Evet' : 'Hayir'}</p>
      <p>Projeksiyon: {data.hasProjector ? 'Evet' : 'Hayir'}</p>
      <img src={data.photoUrl} alt={`Sinif ${data.className} Fotoğrafi`} />
    </div>
  );
};

export default ClassComponent;