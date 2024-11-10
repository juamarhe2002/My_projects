import React from 'react';
import TicketForm from '../components/TicketForm.jsx';
import { useParams, useNavigate } from 'react-router-dom';

function EditTicketPage() {
    const { ticketId } = useParams();
    const navigate = useNavigate();

    const handleSave = () => {
        navigate('/tickets');
    };

    return (
        <div className="mt-5">
            <h2>Edit Ticket</h2>
            <TicketForm ticketId={ticketId} onSave={handleSave} />
        </div>
    );
}

export default EditTicketPage;
