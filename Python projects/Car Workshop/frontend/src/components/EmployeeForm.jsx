// src/components/EmployeeForm.jsx
import React, { useState } from 'react';
import api from '../api';

function EmployeeForm({ onSave }) {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [priceperhour, setPricePerHour] = useState(0);

    /*
    useEffect(() => {
        if (employeeId) {
            fetchEmployee();
        }
    }, [employeeId]);

    const fetchEmployee = async () => {
        try {
            const response = await api.get(`/api/employees/${employeeId}/`);
            setEmployee(response.data);
        } catch (error) {
            console.error('Failed to fetch employee', error);
        }
    };
    

    const handleChange = (e) => {
        const { name, value } = e.target;
        setEmployee({ ...employee, [name]: value });
    };
    */
    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            await api.post('/api/employees/create/', {username, password, Employee: {"PricePerHour" : priceperhour}});
            onSave();
        } catch (error) {
            console.error('Failed to create employee', error);
        }
    };

    return (
        <div className='container'>
            <form onSubmit={handleSubmit} className="mt-3">
                <div className="form-group">
                    <label htmlFor="username">Employee Name</label>
                    <input
                        type="text"
                        className="form-control"
                        id="username"
                        name="username"
                        value={username}
                        onChange={(e) => setUsername(e.target.value)}
                        required
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="password">Password</label>
                    <input
                        type="password"
                        className="form-control"
                        id="password"
                        name="password"
                        value={password}
                        onChange={(e) => setPassword(e.target.value)}
                        required
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="Employee">Price Per Hour (USD)</label>
                    <input
                        type="number"
                        className="form-control"
                        id="Employee"
                        name="Employee"
                        value={priceperhour}
                        onChange={(e) => setPricePerHour(e.target.value)}
                        required
                    />
                </div>
                <button type="submit" className="btn btn-primary mt-1">
                    Add Employee
                </button>
            </form>
        </div>
    );
}

export default EmployeeForm;
