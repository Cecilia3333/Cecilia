package com.openlab;

import java.util.List;

public class TestDao {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		 Dao  dao = new Dao();
		List<Employee>  es= dao.findAll();
		System.out.println(es);
		 
	}

}
