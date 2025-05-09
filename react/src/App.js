import React, { useState } from 'react';
import LessonComponent from './components/LessonComponent';
import BuildingComponent from './components/BuildingComponent';
import ClassComponent from './components/ClassComponent';
import InstructorComponent from './components/InstructorComponent';
import ScheduleComponent from './components/ScheduleComponent';
import UserList from './components/UserList';
import './App.css';

const App = () => {
  const [lessonList, setLessonList] = useState([]);
  const [newLesson, setNewLesson] = useState({
    id: null,
    lessonName: '',
    code: '',
    theoryHours: 0,
    practiceHours: 0,
    purpose: '',
    outcomes: '',
    weeklyTopics: '',
    instructorId: null,
  });

  const [newInstructor, setNewInstructor] = useState({
    id: null,
    firstName: '',
    lastName: '',
    title: '',
  });

  const [editingLessonIndex, setEditingLessonIndex] = useState(null);
  const [editingInstructorIndex, setEditingInstructorIndex] = useState(null);

  const [buildingList, setBuildingList] = useState([]);
  const [classList, setClassList] = useState([]);
  const [instructorList, setInstructorList] = useState([]);
  const [scheduleList, setScheduleList] = useState([]);

  const [activeTab, setActiveTab] = useState('lessons');

  const handleLessonInputChange = (e) => {
    const { name, value } = e.target;
    setNewLesson((prevLesson) => ({ ...prevLesson, [name]: value }));
  };

  const handleInstructorInputChange = (e) => {
    const { name, value } = e.target;
    setNewInstructor((prevInstructor) => ({ ...prevInstructor, [name]: value }));
  };

  const handleLessonAdd = () => {
    if (editingLessonIndex !== null) {

      const updatedList = [...lessonList];
      updatedList[editingLessonIndex] = newLesson;
      setLessonList(updatedList);
      setEditingLessonIndex(null);
    } else {
      setLessonList((prevList) => [...prevList, { ...newLesson, id: Date.now() }]);
    }

    setNewLesson({
      id: null,
      lessonName: '',
      code: '',
      theoryHours: 0,
      practiceHours: 0,
      purpose: '',
      outcomes: '',
      weeklyTopics: '',
      instructorId: null,
    });
  };

  const handleInstructorAdd = () => {
    setInstructorList((prevList) => [...prevList, { ...newInstructor, id: Date.now() }]);
    setNewInstructor({
      id: null,
      firstName: '',
      lastName: '',
      title: '',
    });
  };

  const handleLessonDelete = (id) => {
    const updatedList = lessonList.filter((lesson) => lesson.id !== id);
    setLessonList(updatedList);
  };

  const handleInstructorDelete = (id) => {
    const updatedList = instructorList.filter((instructor) => instructor.id !== id);
    setInstructorList(updatedList);
  };

  const handleLessonUpdate = (index) => {
    setEditingLessonIndex(index);
    setNewLesson(lessonList[index]);
  };

  const handleInstructorUpdate = (index) => {
    setEditingInstructorIndex(index);
    setNewInstructor(instructorList[index]);
  };
  let activeList, activeComponent;
  switch (activeTab) {
    case 'buildings':
      activeList = buildingList;
      activeComponent = BuildingComponent;
      break;
    case 'classes':
      activeList = classList;
      activeComponent = ClassComponent;
      break;
    case 'instructors':
      activeList = instructorList;
      activeComponent = InstructorComponent;
      break;
    case 'schedules':
      activeList = scheduleList;
      activeComponent = ScheduleComponent;
      break;
    default:
      activeList = lessonList;
      activeComponent = LessonComponent;
  }

  return (
    <div className="w3-container">
      <h1>Yönetim Paneli</h1>
      <div>
        <button onClick={() => setActiveTab('lessons')}>Dersler</button>
        <button onClick={() => setActiveTab('buildings')}>Binalar</button>
        <button onClick={() => setActiveTab('classes')}>Siniflar</button>
        <button onClick={() => setActiveTab('instructors')}>Öğretim Elemanlari</button>
        <button onClick={() => setActiveTab('schedules')}>Ders Programlari</button>
      </div>

      <h1>Ders Yönetimi</h1>

      <div>
        <label htmlFor="lessonName">Ders Adi:</label>
        <input
          type="text"
          id="lessonName"
          name="lessonName"
          value={newLesson.lessonName}
          onChange={handleLessonInputChange}
        />
        <label htmlFor="code">Ders Kodu:</label>
        <input
          type="text"
          id="code"
          name="code"
          value={newLesson.code}
          onChange={handleLessonInputChange}
        />
        <label htmlFor="purpose">Amaç:</label>
        <input
          type="text"
          id="purpose"
          name="purpose"
          value={newLesson.purpose}
          onChange={handleLessonInputChange}
        />
        <label htmlFor="instructorId">Öğretmen:</label>
        <select
          id="instructorId"
          name="instructorId"
          value={newLesson.instructorId || ''}
          onChange={handleLessonInputChange}
        >
          <option value="">Öğretmen Seç</option>
          {instructorList.map((instructor) => (
            <option key={instructor.id} value={instructor.id}>
              {instructor.firstName} {instructor.lastName}
            </option>
          ))}
        </select>
        <button onClick={handleLessonAdd}>
          {editingLessonIndex !== null ? 'Dersi Güncelle' : 'Ders Ekle'}
        </button>
      </div>

      <div>
        <label htmlFor="firstName">Adi:</label>
        <input
          type="text"
          id="firstName"
          name="firstName"
          value={newInstructor.firstName}
          onChange={handleInstructorInputChange}
        />
        <label htmlFor="lastName">Soyadi:</label>
        <input
          type="text"
          id="lastName"
          name="lastName"
          value={newInstructor.lastName}
          onChange={handleInstructorInputChange}
        />
        <label htmlFor="title">Unvani:</label>
        <input
          type="text"
          id="title"
          name="title"
          value={newInstructor.title}
          onChange={handleInstructorInputChange}
        />
        <button onClick={handleInstructorAdd}>Öğretmen Ekle</button>
      </div>

      <div>
        <h2>Ders Listesi</h2>
        <ul>
          {lessonList.map((lesson, index) => (
            <li key={lesson.id}>
              {lesson.lessonName} - {lesson.code} - Amaç: {lesson.purpose} - Öğretmen: {lesson.instructorId}
              <button onClick={() => handleLessonUpdate(index)}>Güncelle</button>
              <button onClick={() => handleLessonDelete(lesson.id)}>Sil</button>
            </li>
          ))}
        </ul>
      </div>

      <div>
        <h2>Öğretmen Listesi</h2>
        <ul>
          {instructorList.map((instructor, index) => (
            <li key={instructor.id}>
              {instructor.firstName} {instructor.lastName} - Unvan: {instructor.title}
              <button onClick={() => handleInstructorUpdate(index)}>Güncelle</button>
              <button onClick={() => handleInstructorDelete(instructor.id)}>Sil</button>
            </li>
          ))}
        </ul>
      </div>
      <UserList />
    </div>
  );
};

export default App;