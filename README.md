🏥 Hospital Management System (C++)

A console-based Hospital Management System built using C++ (OOP principles).
This project manages doctors, patients, appointments, and hospital beds using structured architecture and JSON storage.

📌 Features
👨‍⚕️ Doctor Management

Add new doctors

Assign available days (e.g., Monday, Friday, etc.)

View booked appointment slots

Display patient names for each booked slot

🧑‍🤝‍🧑 Patient Management

Register new patients

Book appointments based on doctor's availability

Prevent double booking of time slots

📅 Appointment System

Patients choose a day

System shows only doctors available on that day

Book appointment with time slot

Store appointments persistently in JSON

🛏 Bed Management

Set total number of beds (e.g., 100 beds)

Track occupied / available beds

Admit and discharge patients

💾 Data Storage

Uses JSON files inside:

src/storage/
    doctors.json
    patients.json
    appointments.json
    beds.json

🏗 Project Structure
src/
│
├── core/
│   ├── doctor.h
│   ├── patient.h
│   ├── appointment.h
│   ├── bed.h
│   └── hospital.h
│
├── services/
│   ├── doctor_service.h
│   ├── patient_service.h
│   └── appointment_service.h
│
├── storage/
│   ├── doctors.json
│   ├── patients.json
│   ├── appointments.json
│   └── beds.json
│
└── main.cpp

🧠 OOP Concepts Used

Classes & Objects

Encapsulation

Separation of Concerns

Service Layer Architecture

File-based Persistence (JSON)

STL (vector, string, etc.)
