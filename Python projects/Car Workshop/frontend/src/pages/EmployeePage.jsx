// src/pages/EmployeePage.jsx
import React, { useState, useEffect } from 'react';
import api from '../api.js';
import EmployeeForm from '../components/EmployeeForm.jsx';
import Navbar from '../components/NavBar.jsx';

function EmployeePage() {
    const [employees, setEmployees] = useState([]);

    useEffect(() => {
        fetchEmployees();
    }, []);

    const fetchEmployees = async () => {
        try {
            const response = await api.get('/api/employees/');
            setEmployees(response.data);
        } catch (error) {
            console.error('Failed to fetch employees', error);
        }
    };

    const deleteEmployee = async (id) => {
        try {
            await api.delete(`/api/employees/delete/${id}/`);
            fetchEmployees();
        } catch (error) {
            console.error('Failed to delete employee', error);
        }
    };

    const handleSave = () => {
        fetchEmployees();
    };

    return (
        <div className='container'>
            <Navbar></Navbar>
            <div className="mt-1">
                <h2>Employee Management</h2>
                <hr />
                <h4>Create New Employee</h4>
                <EmployeeForm onSave={handleSave} />
                <hr />
                <h4>Employee List</h4>
                <ul className="list-group mt-3">
                    {employees.map(emp => (
                        <li key={emp.id} className="list-group-item d-flex justify-content-between align-items-center">
                            {emp.username} - {emp.Employee.PricePerHour} USD/hour
                            <div>
                                <button className="btn btn-danger" onClick={() => deleteEmployee(emp.id)}>
                                    Delete
                                </button>
                            </div>
                        </li>
                    ))}
                </ul>
            </div>
        </div>
    );
}

export default EmployeePage;
