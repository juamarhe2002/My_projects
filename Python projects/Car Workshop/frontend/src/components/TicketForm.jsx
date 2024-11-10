import React, { useState, useEffect } from 'react';
import api from '../api';

function TicketForm({ ticketId, onSave }) {
    const [ticket, setTicket] = useState({
        Brand: '',
        Model: '',
        RegistrationId: '',
        Problem: '',
        EmployeeAssigned: 'None',
        Status: 'Created',
        TotalPrice: 0,
        Estimate: {
            'Description': 'Estimate description',
            'ExpectedCost': 0,
            'Accepted': false
        }
    });

    useEffect(() => {
        if (ticketId) {
            fetchTicket();
        }
    }, [ticketId]);

    const fetchTicket = async () => {
        try {
            const response = await api.get(`/api/tickets/edit/${ticketId}/`);
            setTicket(response.data);
        } catch (error) {
            console.error('Failed to fetch ticket', error);
        }
    };

    const handleChange = (e) => {
        const { name, value } = e.target;
        setTicket({ ...ticket, [name]: value });
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            if (ticketId) {
                await api.put(`/api/tickets/edit/${ticketId}/`, ticket);
            } else {
                await api.post('/api/tickets/create/', ticket);
            }
            onSave();
        } catch (error) {
            console.error('Failed to save ticket', error);
        }
    };

    return (
        <form onSubmit={handleSubmit} className="mt-3">
            <div className="form-group">
                <label htmlFor="Brand">Brand</label>
                <input
                    type="text"
                    className="form-control"
                    id="Brand"
                    name="Brand"
                    value={ticket.Brand}
                    onChange={handleChange}
                    required
                />
            </div>
            <div className="form-group">
                <label htmlFor="Model">Model</label>
                <input
                    type="text"
                    className="form-control"
                    id="Model"
                    name="Model"
                    value={ticket.Model}
                    onChange={handleChange}
                    required
                />
            </div>
            <div className="form-group">
                <label htmlFor="RegistrationId">Registration ID</label>
                <input
                    type="text"
                    className="form-control"
                    id="RegistrationId"
                    name="RegistrationId"
                    value={ticket.RegistrationId}
                    onChange={handleChange}
                    required
                />
            </div>
            <div className="form-group">
                <label htmlFor="Problem">Description of Problem</label>
                <textarea
                    className="form-control"
                    id="Problem"
                    name="Problem"
                    value={ticket.Problem}
                    onChange={handleChange}
                    required
                ></textarea>
            </div>
            <button type="submit" className="btn btn-primary">
                {ticketId ? 'Update Ticket' : 'Create Ticket'}
            </button>
        </form>
    );
}

export default TicketForm;
