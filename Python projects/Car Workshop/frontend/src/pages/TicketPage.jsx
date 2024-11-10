import React, { useState, useEffect } from 'react';
import api from '../api.js';
import Navbar from '../components/NavBar.jsx';
import { Link, useNavigate } from 'react-router-dom';

function TicketPage() {
    const [tickets, setTickets] = useState([]);
    const [selectedTicketId, setSelectedTicketId] = useState(null);
    const navigate = useNavigate();

    useEffect(() => {
        fetchTickets();
    }, []);

    const fetchTickets = async () => {
        try {
            const response = await api.get('/api/tickets/');
            setTickets(response.data);
        } catch (error) {
            console.error('Failed to fetch tickets', error);
        }
    };

    const deleteTicket = async (id) => {
        try {
            await api.delete(`/api/tickets/delete/${id}/`);
            fetchTickets();
        } catch (error) {
            console.error('Failed to delete ticket', error);
        }
    };

    const handleSave = () => {
        fetchTickets();
        setSelectedTicketId(null);  // Reset the form
    };

    const updateTicketStatus = async (id, status) => {
        let new_status = "None";
        if(status === "Created"){
            new_status = "In Progress";
        }else if(status === "In Progress"){
            new_status = "Done"
        }else if(status === "Done"){
            new_status = "Closed"
        }else {
            new_status = "Closed"
        }

        try {
            const res = await api.get("/api/employees/employee/");
            await api.patch(`/api/tickets/edit/${id}/`, {'EmployeeAssigned': res.data,'Status':new_status });
            fetchTickets();
        } catch (error) {
            console.error('Failed to update ticket state', error);
        }
    };

    return (
        <div className='container'>
            <Navbar></Navbar>
            <div className="mt-1">
                <div className="d-flex justify-content-between align-items-center">
                    <h2>Ticket Management</h2>
                    <Link to="/tickets/create" className="btn btn-primary">Create New Ticket</Link>
                </div>
                <hr />
                <ul className="list-group mt-3">
                    {tickets.map(ticket => (
                        <li key={ticket.id} className="list-group-item d-flex justify-content-between align-items-center">
                            {ticket.Brand} {ticket.Model} - {ticket.RegistrationId}
                            <div>
                                <button className="btn btn-info mr-2" onClick={() => updateTicketStatus(ticket.id, ticket.Status)}>{ticket.Status}</button>
                                <button className="btn btn-warning mr-2" onClick={() => navigate(`/tickets/edit/${ticket.id}`)}>Edit</button>
                                <button className="btn btn-secondary" onClick={() => navigate(`/tickets/view/${ticket.id}`)}>View</button>
                                <button className="btn btn-danger" onClick={() => deleteTicket(ticket.id)}>Delete</button>
                            </div>
                        </li>
                    ))}
                </ul>
            </div>
        </div>
    );
}

export default TicketPage;
