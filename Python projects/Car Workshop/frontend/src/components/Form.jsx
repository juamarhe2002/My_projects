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

    return <div className="d-flex align-items-center justify-content-center vh-100">
        <form onSubmit={handleSubmit} className="mb-9">
            <div className="form-group mb-3">
                <h1>{name}</h1>
            </div>
            <div className="form-group mb-3">
                <input type="text" className="form-control" value={username} onChange={(e) => setUsername(e.target.value)} placeholder="Username" required/>
                <div className="invalid-feedback">Please enter an username!</div>
            </div>
            <div className="form-group mb-3">
                <input type="password" className="form-control" value={password} onChange={(e) => setPassword(e.target.value)} placeholder="Password" required/>
                <div className="invalid-feedback">Please enter your password!</div>
            </div>
            <button type="submit" className="btn btn-primary mb-3">{name}</button>
        </form>
    </div> 
}

export default Form;