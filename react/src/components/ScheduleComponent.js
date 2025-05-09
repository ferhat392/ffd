import React from 'react';

const ScheduleComponent = ({ data }) => {
  return (
    <div>
      <h3>{data.lessonCode}</h3>
      <p>Gün: {data.day}</p>
      <p>Saat: {data.time}</p>
      <p>Sinif: {data.className}</p>
      <p>Öğretim Elemani: {data.instructorName}</p>
    </div>
  );
};

export default ScheduleComponent;