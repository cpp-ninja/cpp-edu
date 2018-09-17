struct Singleton {

	static Singleton & instance() {
		static Singleton s ;
		return s ;
	}	
	Data & data() {
	 return data_ ; 
	}
private :
	Singleton() {}
	Singleton(Singleton const &);
	Singleton & operator =(Singleton const &);
	Data data_ ;
};

int main ()
{
	// первое обращение
	Singleton & s = Singleton::instance();
	Data d = s.data ();

	// аналогично d = s.data();
	d = Singleton :: instance().data();
return 0;
}