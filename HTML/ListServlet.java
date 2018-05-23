package com.openlab;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ListServlet   extends  HttpServlet{

	@Override
	protected void service(HttpServletRequest request, 
			HttpServletResponse response)
			throws ServletException, IOException {
		// TODO Auto-generated method stub
//		 Employee e = new  Employee(1001, "tom", "PM", 20000, 30);
		 
		  Dao  dao = new  Dao();
		  ArrayList<Employee>  es = dao.findAll();
		  
		
		 request.setAttribute("es", es);
		 request.getRequestDispatcher("emplist1.jsp").forward(request, response);
	}
	
}
