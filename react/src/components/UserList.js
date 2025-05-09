import React, { useState, useEffect } from 'react';

const UserList = () => {
  const [users, setUsers] = useState([]);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch('/data.json');

        if (!response.ok) {
          throw new Error('Network response was not ok');
        }

        const data = await response.json();

        setUsers(data.users);
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    };

    fetchData();
  }, []);

  return (
    <div>
      <h2>Binalar</h2>
      <ul>
        {users.map((user) => (
          <li key={user.id}>{user.name} - {user.lesson} - {user.kod}</li>
        ))}
      </ul>

    </div>
  );
};

export default UserList;