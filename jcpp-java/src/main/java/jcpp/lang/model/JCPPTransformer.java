package jcpp.lang.model;

import javax.xml.bind.annotation.*;
import java.util.*;

public interface JCPPTransformer{
	public void tranform(JavaInterface ji, CPPInterface ci);
}