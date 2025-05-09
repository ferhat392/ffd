import React from 'react';

const BuildingComponent = ({ data }) => {
  return (
    <div>
      <h3>{data.name}</h3>
      <p>Konum: {data.location}</p>
      <p>Adres: {data.address}</p>
      <p>Asansörlü: {data.hasElevator ? 'Evet' : 'Hayir'}</p>
      <p>Engelli Dostu: {data.isAccessible ? 'Evet' : 'Hayir'}</p>
      <p>Rampa Var: {data.hasRamp ? 'Evet' : 'Hayir'}</p>
      <p>Bina Kodu: {data.code}</p>
    </div>
  );
};

export default BuildingComponent;