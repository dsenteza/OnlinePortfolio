import React, { Component } from 'react';
import './App.css';
import Todo from './Todo';
import NewTodo from './NewTodo';

class App extends Component {
  render() {
    return (
      <div className="App">
        	<h1>Dominique's ToDo App</h1>
        	<section id="todoApp">
      		</section>
      		<section id="todos">
      			<NewTodo />
        		<Todo />
      		</section>
      </div>
    );
  }
}

export default App;
