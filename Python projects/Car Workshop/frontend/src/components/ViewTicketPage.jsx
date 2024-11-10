import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import api from '../api';

function ViewTicketPage() {
    const { ticketId } = useParams();
    const [ticket, setTicket] = useState(null);

    useEffect(() => {
        fetchTicket();
    }, []);

    const fetchTicket = async () => {
        try {
            const response = await api.get(`/api/tickets/edit/${ticketId}/`);
            setTicket(response.data);
        } catch (error) {
            console.error('Failed to fetch ticket', error);
        }
    };

    if (!ticket) return <div>Loading...</div>;

    return (
        <div className="mt-5">
            <h2>Ticket Details</h2>
            <p><strong>Brand:</strong> {ticket.Brand}</p>
            <p><strong>Model:</strong> {ticket.Model}</p>
            <p><strong>Registration ID:</strong> {ticket.RegistrationId}</p>
            <p><strong>Description:</strong> {ticket.Problem}</p>
            <p><strong>Assigned Employee:</strong> {ticket.EmployeeAssigned}</p>
            <p><strong>Time Slots:</strong> None </p>
            <p><strong>Status:</strong> {ticket.Status}</p>
            <p><strong>Estimate Accepted:</strong> {ticket.Estimate.Accepted}</p>
            <p><strong>Parts:</strong> None </p>
            <p><strong>Total Price:</strong> {ticket.TotalPrice}</p>
        </div>
    );
}

export default ViewTicketPage;
