import React, {useState, useEffect} from "react"
import api from "../api";
import Navbar from "../components/NavBar";

function Home() {
    const [tickets, setTickets] = useState([]);

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

    return <div className="container">
        <Navbar></Navbar>
        <h2>Car Workshop Homepage</h2>
        <hr />
        <h4>Your tickets:</h4>
        <ul className="list-group mt-3">
            {tickets.map(ticket => (
                <li key={ticket.id} className="list-group-item d-flex justify-content-between align-items-center">
                    {ticket.Brand} {ticket.Model} - {ticket.RegistrationId}
                    <div>
                        <label htmlFor="ticket.Status">{ticket.Status}</label>
                    </div>
                </li>
            ))}
        </ul>
    </div>
}

export default Home;