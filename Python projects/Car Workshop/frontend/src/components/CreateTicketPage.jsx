import React from 'react';
import TicketForm from '../components/TicketForm.jsx';
import { useNavigate } from 'react-router-dom';

function CreateTicketPage() {
    const navigate = useNavigate();

    const handleSave = () => {
        navigate('/tickets');
    };

    return (
        <div className='container'>
            <div className="mt-5">
                <h2>Create New Ticket</h2>
                <hr />
                <TicketForm onSave={handleSave} />
            </div>
        </div> 
    );
}

export default CreateTicketPage;
