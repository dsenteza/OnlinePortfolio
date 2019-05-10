import React, { Component } from 'react';
import './NewTodo.css';

class NewTodo extends Component {
  render() {
    return (
    	<aside>
				<form id="toDoForm">
					<div class="row">
						<p class="blank col-md-3 col-sm-1 col-1"></p>
						<input type="text" name="taskText" placeholder="Type New Task Here..." id="newTitle" class="col-8 col-sm-8 col-md-5"/>
						<button id="submit" class="col-2 col-sm-2 col-md-1">+</button>
						<p class="blank col-md-3 col-sm-1 col-1"></p>
					</div>
				</form>
		</aside>
    );
  }
}

export default NewTodo;
