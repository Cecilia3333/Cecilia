package com.openlab;

import java.io.IOException;
import java.io.PrintWriter;


import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

//   服务器 端编程  
public class RegistServelt  extends  HttpServlet{

	@Override
	protected void service(HttpServletRequest request,
			HttpServletResponse response)
			throws ServletException, IOException {
		    response.setContentType("text/html; charset=UTF-8");
//		 请求  客户端  向 服务器  发数据 
//		响应    服务器  向客户端  回传数据
		    	String  id= request.getParameter("username");
		    	String  name  = request.getParameter("name");
                String  pwd   = request.getParameter("pwd");
                String  sex   = request.getParameter("sex");
                System.out.println(id+name+pwd+sex);
//                PrintWriter  out = response.getWriter();
                if(id.equals("17782561601")){
                	System.out.println("此用户已经注册过");
                	
//                	out.println("此用户已经注册过");
                	request.setAttribute("message", "此用户已经注册过");
//                	 转发 
                	request.getRequestDispatcher("regist.jsp").forward(request, response);
                	
                	
                	 
                }else {
                	System.out.println("执行 插入操作");
                	System.out.println("注册成功");
//                	告诉浏览器  向  参数 代表的路径    发送请求
                	response.sendRedirect("list");
//                	request.setAttribute("message", "注册成功");
////               	 转发 
//               	request.getRequestDispatcher("regist.jsp").forward(request, response);
////                	out.println("注册成功");
                }
		
	}

	
		
}
