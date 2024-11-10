import { useState } from "react";
import api from "../api";
import { useNavigate } from "react-router-dom";
import { ACCESS_TOKEN, REFRESH_TOKEN } from "../constants";

function Form({route, method}) {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [loading, setLoading] = useState(false);
    const navigate = useNavigate();

    const name = method === "login" ? "Login" : "Register";

    const handleSubmit = async (e) => {
        setLoading(true);
        e.preventDefault();

        try {
            const res = await api.post(route, {username, password});
            if(method === "login"){
                localStorage.setItem(ACCESS_TOKEN, res.data.access);
                localStorage.setItem(REFRESH_TOKEN, res.data.refresh);
                navigate("/");
            }else {
                navigate("/login");
            }
        } catch (error) {
            alert(error)
        } finally {
            setLoading(false)
        }
    }

    return <div className="container">
    <form onSubmit={handleSubmit}>
        <h1>{name}</h1>
        <input type="text" className="form-control" value={username} onChange={(e) => setUsername(e.target.value)} placeholder="Username"/>
        <input type="password" className="form-control" value={password} onChange={(e) => setPassword(e.target.value)} placeholder="Password"/>
        <button type="submit" className="btn btn-primary">{name}</button>
    </form>
    </div> 
}

export default Form;