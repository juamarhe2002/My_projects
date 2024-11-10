import React from "react";

function Note({note, onDelete}) {
    const formattedDate = new Date(note.created_at).toLocaleDateString("en-US");

    return <div className="container">
        <h4>{note.title}</h4>
        <p>{note.content}</p>
        <p>{formattedDate}</p>
        <button className="btn btn-danger" onClick={() => onDelete(note.id)}>Delete</button>
    </div>
}

export default Note;