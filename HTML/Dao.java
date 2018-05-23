package com.openlab;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;


// 封装    数据的操作 
public class Dao {
	public    ArrayList<Employee>    findAll(){
		ArrayList<Employee>  es = new ArrayList<Employee>();
		 try {
			Class.forName("com.mysql.jdbc.Driver");
			Connection  conn = DriverManager.getConnection(
					"jdbc:mysql://127.0.0.1:3309/web", "root", "1234");
			Statement  state = conn.createStatement();
			ResultSet   rs = state.executeQuery("select * from emp");
			while (rs.next()) {
				int  eno =  rs.getInt("eno");
				String ename = rs.getString("ename");
				String job   = rs.getString("job");
				double  salary = rs.getDouble("salary");
				Employee  e = new  Employee(eno, ename, job, salary, 20);
				es.add(e);
			}
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		 
		
		
		return  es;
	}
	
	
}
