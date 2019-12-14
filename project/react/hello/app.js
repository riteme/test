import React from 'react'
import ReactDOM from 'react-dom'

class App extends React.Component {
    render() {
        return (
            <p>Hello, world!</p>
        );
    }
}

const container = document.getElementById('app-root')
ReactDOM.render(
    <App />,
    container
);