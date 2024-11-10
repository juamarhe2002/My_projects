import React from "react";
import { BrowserRouter, Route, Routes, Navigate } from "react-router-dom";
import Login from "./pages/Login";
import Register from "./pages/Register";
import Home from "./pages/Home";
import NotFound from "./pages/NotFound";
import ProtectedRoute from "./components/ProtectedRoute";
import EmployeePage from './pages/EmployeePage.jsx';
import TicketPage from './pages/TicketPage.jsx';
import CreateTicketPage from "./components/CreateTicketPage.jsx";
import EditTicketPage from "./components/EditTicketPage.jsx";
import ViewTicketPage from "./components/ViewTicketPage.jsx";

function Logout() {
  localStorage.clear();
  return <Navigate to="/login" />
}

function App() {

  return (
    <BrowserRouter>
      <Routes>
        <Route 
          path="/"
          element={
            <ProtectedRoute>
              <Home />
            </ProtectedRoute>
          }
        />
        <Route 
          path="/employees"
          element={
            <ProtectedRoute>
              <EmployeePage></EmployeePage>
            </ProtectedRoute>
          }
        />
        <Route 
          path="/tickets"
          element={
            <ProtectedRoute>
              <TicketPage></TicketPage>
            </ProtectedRoute>
          }
        />
        <Route path="/tickets/create" element={<ProtectedRoute><CreateTicketPage/></ProtectedRoute>}/>
        <Route path="/tickets/edit/:ticketId" element={<ProtectedRoute><EditTicketPage/></ProtectedRoute>}/>
        <Route path="/tickets/view/:ticketId" element={<ProtectedRoute><ViewTicketPage/></ProtectedRoute>}/>
        <Route path="/login" element={<Login />}/>
        <Route path="/logout" element={<Logout />}/>
        <Route path="*" element={<NotFound />} />
      </Routes>
    </BrowserRouter>
  )
}

export default App
