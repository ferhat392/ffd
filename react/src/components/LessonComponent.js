import React from 'react';

const LessonComponent = ({ data }) => {
  return (
    <div>
      <h3>{data.code}</h3>
      <p>Teorik Saat: {data.theoryHours}</p>
      <p>Uygulama Saat: {data.practiceHours}</p>
      <p>Amaç: {data.purpose}</p>
      <p>Öğrenim Çiktilari: {data.outcomes}</p>
      <p>Haftalik Ders Konulari: {data.weeklyTopics}</p>
    </div>
  );
};

export default LessonComponent;