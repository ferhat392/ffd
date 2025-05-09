import React from 'react';

const InstructorComponent = ({ data }) => {
  return (
    <div>
      <h3>{`${data.title} ${data.firstName} ${data.lastName}`}</h3>
      <p>TC Kimlik No: {data.tcId}</p>
      <p>Ünvan: {data.title}</p>
      <p>Kullanici Adi: {data.username}</p>
    </div>
  );
};

export default InstructorComponent;