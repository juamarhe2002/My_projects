import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import api from '../api';
import Navbar from "../components/NavBar";

function ViewTicketPage() {
    const { ticketId } = useParams();
    const [ticket, setTicket] = useState(null);

    useEffect(() => {
        fetchTicket();
    }, []);

    const fetchTicket = async () => {
        try {
            const response = await api.get(`/api/tickets/view/${ticketId}/`);
            setTicket(response.data);
        } catch (error) {
            console.error('Failed to fetch ticket', error);
        }
    };

    if (!ticket) return <div>Loading...</div>;

    return (
        <div>
            <Navbar></Navbar>
            <div className='mt-3'>
                <ul class="list-group">
                    <li class="list-group-item"><h2>Ticket Details</h2></li>
                    <li class="list-group-item"><p><strong>Brand:</strong> {ticket.Brand}</p></li>
                    <li class="list-group-item"><p><strong>Model:</strong> {ticket.Model}</p></li>
                    <li class="list-group-item"><p><strong>Registration ID:</strong> {ticket.RegistrationId}</p></li>
                    <li class="list-group-item"><p><strong>Description:</strong> {ticket.Problem}</p></li>
                    <li class="list-group-item"><p><strong>Assigned Employee:</strong> {ticket.EmployeeAssigned}</p></li>
                    <li class="list-group-item"><p><strong>Time Slots:</strong> None </p></li>
                    <li class="list-group-item"><p><strong>Status:</strong> {ticket.Status}</p></li>
                    <li class="list-group-item"><p><strong>Estimate Accepted:</strong> {ticket.Estimate.Accepted}</p></li>
                    <li class="list-group-item"><p><strong>Parts:</strong> None </p></li>
                    <li class="list-group-item"><p><strong>Total Price:</strong> {ticket.TotalPrice}</p></li>
                </ul>    
            </div>
        </div>
    );
}

export default ViewTicketPage;
